#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct local_zones {int /*<<< orphan*/  lock; } ;
struct local_zone {int /*<<< orphan*/  lock; int /*<<< orphan*/ * soa; int /*<<< orphan*/  name; } ;
struct local_data {int /*<<< orphan*/  name; int /*<<< orphan*/ * rrsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_DS ; 
 int /*<<< orphan*/  del_empty_term (struct local_zone*,struct local_data*,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  del_local_rrset (struct local_data*,int /*<<< orphan*/ ) ; 
 struct local_zone* local_zones_lookup (struct local_zones*,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 
 struct local_data* lz_find_node (struct local_zone*,int /*<<< orphan*/ *,size_t,int) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void local_zones_del_data(struct local_zones* zones, 
	uint8_t* name, size_t len, int labs, uint16_t dclass)
{
	/* find zone */
	struct local_zone* z;
	struct local_data* d;

	/* remove DS */
	lock_rw_rdlock(&zones->lock);
	z = local_zones_lookup(zones, name, len, labs, dclass, LDNS_RR_TYPE_DS);
	if(z) {
		lock_rw_wrlock(&z->lock);
		d = lz_find_node(z, name, len, labs);
		if(d) {
			del_local_rrset(d, LDNS_RR_TYPE_DS);
			del_empty_term(z, d, name, len, labs);
		}
		lock_rw_unlock(&z->lock);
	}
	lock_rw_unlock(&zones->lock);

	/* remove other types */
	lock_rw_rdlock(&zones->lock);
	z = local_zones_lookup(zones, name, len, labs, dclass, 0);
	if(!z) {
		/* no such zone, we're done */
		lock_rw_unlock(&zones->lock);
		return;
	}
	lock_rw_wrlock(&z->lock);
	lock_rw_unlock(&zones->lock);

	/* find the domain */
	d = lz_find_node(z, name, len, labs);
	if(d) {
		/* no memory recycling for zone deletions ... */
		d->rrsets = NULL;
		/* did we delete the soa record ? */
		if(query_dname_compare(d->name, z->name) == 0)
			z->soa = NULL;

		/* cleanup the empty nonterminals for this name */
		del_empty_term(z, d, name, len, labs);
	}

	lock_rw_unlock(&z->lock);
}
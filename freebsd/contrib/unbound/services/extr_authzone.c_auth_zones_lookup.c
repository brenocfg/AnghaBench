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
struct regional {int dummy; } ;
struct query_info {int /*<<< orphan*/  qclass; } ;
struct dns_msg {int dummy; } ;
struct auth_zones {int /*<<< orphan*/  lock; } ;
struct auth_zone {int fallback_enabled; int /*<<< orphan*/  lock; scalar_t__ zone_expired; int /*<<< orphan*/  for_upstream; } ;

/* Variables and functions */
 struct auth_zone* auth_zone_find (struct auth_zones*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int auth_zone_generate_answer (struct auth_zone*,struct query_info*,struct regional*,struct dns_msg**,int*) ; 
 int /*<<< orphan*/  lock_rw_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 

int auth_zones_lookup(struct auth_zones* az, struct query_info* qinfo,
	struct regional* region, struct dns_msg** msg, int* fallback,
	uint8_t* dp_nm, size_t dp_nmlen)
{
	int r;
	struct auth_zone* z;
	/* find the zone that should contain the answer. */
	lock_rw_rdlock(&az->lock);
	z = auth_zone_find(az, dp_nm, dp_nmlen, qinfo->qclass);
	if(!z) {
		lock_rw_unlock(&az->lock);
		/* no auth zone, fallback to internet */
		*fallback = 1;
		return 0;
	}
	lock_rw_rdlock(&z->lock);
	lock_rw_unlock(&az->lock);

	/* if not for upstream queries, fallback */
	if(!z->for_upstream) {
		lock_rw_unlock(&z->lock);
		*fallback = 1;
		return 0;
	}
	if(z->zone_expired) {
		*fallback = z->fallback_enabled;
		lock_rw_unlock(&z->lock);
		return 0;
	}
	/* see what answer that zone would generate */
	r = auth_zone_generate_answer(z, qinfo, region, msg, fallback);
	lock_rw_unlock(&z->lock);
	return r;
}
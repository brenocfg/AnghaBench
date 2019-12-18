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
struct local_zones {int /*<<< orphan*/  lock; } ;
struct local_zone {int dummy; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_zones_del_zone (struct local_zones*,struct local_zone*) ; 
 struct local_zone* local_zones_find (struct local_zones*,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_arg_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,size_t*,int*) ; 

__attribute__((used)) static int
perform_zone_remove(RES* ssl, struct local_zones* zones, char* arg)
{
	uint8_t* nm;
	int nmlabs;
	size_t nmlen;
	struct local_zone* z;
	if(!parse_arg_name(ssl, arg, &nm, &nmlen, &nmlabs))
		return 0;
	lock_rw_wrlock(&zones->lock);
	if((z=local_zones_find(zones, nm, nmlen, 
		nmlabs, LDNS_RR_CLASS_IN))) {
		/* present in tree */
		local_zones_del_zone(zones, z);
	}
	lock_rw_unlock(&zones->lock);
	free(nm);
	return 1;
}
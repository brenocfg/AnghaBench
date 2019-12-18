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
struct local_zone {int type; int /*<<< orphan*/  lock; } ;
typedef  enum localzone_type { ____Placeholder_localzone_type } localzone_type ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  find_arg2 (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_zone_str2type (char*,int*) ; 
 int /*<<< orphan*/  local_zones_add_zone (struct local_zones*,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int) ; 
 struct local_zone* local_zones_find (struct local_zones*,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_arg_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,size_t*,int*) ; 
 int /*<<< orphan*/  ssl_printf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int
perform_zone_add(RES* ssl, struct local_zones* zones, char* arg)
{
	uint8_t* nm;
	int nmlabs;
	size_t nmlen;
	char* arg2;
	enum localzone_type t;
	struct local_zone* z;
	if(!find_arg2(ssl, arg, &arg2))
		return 0;
	if(!parse_arg_name(ssl, arg, &nm, &nmlen, &nmlabs))
		return 0;
	if(!local_zone_str2type(arg2, &t)) {
		ssl_printf(ssl, "error not a zone type. %s\n", arg2);
		free(nm);
		return 0;
	}
	lock_rw_wrlock(&zones->lock);
	if((z=local_zones_find(zones, nm, nmlen, 
		nmlabs, LDNS_RR_CLASS_IN))) {
		/* already present in tree */
		lock_rw_wrlock(&z->lock);
		z->type = t; /* update type anyway */
		lock_rw_unlock(&z->lock);
		free(nm);
		lock_rw_unlock(&zones->lock);
		return 1;
	}
	if(!local_zones_add_zone(zones, nm, nmlen, 
		nmlabs, LDNS_RR_CLASS_IN, t)) {
		lock_rw_unlock(&zones->lock);
		ssl_printf(ssl, "error out of memory\n");
		return 0;
	}
	lock_rw_unlock(&zones->lock);
	return 1;
}
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
struct auth_zones {int dummy; } ;
struct auth_zone {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  nm ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_MAX_DOMAINLEN ; 
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 struct auth_zone* auth_zone_create (struct auth_zones*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 struct auth_zone* auth_zone_find (struct auth_zones*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,char*) ; 
 scalar_t__ sldns_str2wire_dname_buf (char*,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static struct auth_zone*
auth_zones_find_or_add_zone(struct auth_zones* az, char* name)
{
	uint8_t nm[LDNS_MAX_DOMAINLEN+1];
	size_t nmlen = sizeof(nm);
	struct auth_zone* z;

	if(sldns_str2wire_dname_buf(name, nm, &nmlen) != 0) {
		log_err("cannot parse auth zone name: %s", name);
		return 0;
	}
	z = auth_zone_find(az, nm, nmlen, LDNS_RR_CLASS_IN);
	if(!z) {
		/* not found, create the zone */
		z = auth_zone_create(az, nm, nmlen, LDNS_RR_CLASS_IN);
	} else {
		lock_rw_wrlock(&z->lock);
	}
	return z;
}
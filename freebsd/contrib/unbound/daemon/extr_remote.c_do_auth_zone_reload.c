#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  cfg; struct auth_zones* auth_zones; } ;
struct worker {TYPE_1__ env; } ;
struct auth_zones {int /*<<< orphan*/  lock; } ;
struct auth_zone {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 struct auth_zone* auth_zone_find (struct auth_zones*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auth_zone_read_zonefile (struct auth_zone*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_arg_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,size_t*,int*) ; 
 int /*<<< orphan*/  send_ok (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_printf (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static void
do_auth_zone_reload(RES* ssl, struct worker* worker, char* arg)
{
	size_t nmlen;
	int nmlabs;
	uint8_t* nm = NULL;
	struct auth_zones* az = worker->env.auth_zones;
	struct auth_zone* z = NULL;
	if(!parse_arg_name(ssl, arg, &nm, &nmlen, &nmlabs))
		return;
	if(az) {
		lock_rw_rdlock(&az->lock);
		z = auth_zone_find(az, nm, nmlen, LDNS_RR_CLASS_IN);
		if(z) {
			lock_rw_wrlock(&z->lock);
		}
		lock_rw_unlock(&az->lock);
	}
	free(nm);
	if(!z) {
		(void)ssl_printf(ssl, "error no auth-zone %s\n", arg);
		return;
	}
	if(!auth_zone_read_zonefile(z, worker->env.cfg)) {
		lock_rw_unlock(&z->lock);
		(void)ssl_printf(ssl, "error failed to read %s\n", arg);
		return;
	}
	lock_rw_unlock(&z->lock);
	send_ok(ssl);
}
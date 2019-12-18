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
struct rsocket {int opts; int keepalive_time; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int RS_OPT_SVC_ACTIVE ; 
 int /*<<< orphan*/  RS_SVC_ADD_KEEPALIVE ; 
 int /*<<< orphan*/  RS_SVC_REM_KEEPALIVE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,int*) ; 
 int rs_notify_svc (int /*<<< orphan*/ *,struct rsocket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_svc ; 

__attribute__((used)) static int rs_set_keepalive(struct rsocket *rs, int on)
{
	FILE *f;
	int ret;

	if ((on && (rs->opts & RS_OPT_SVC_ACTIVE)) ||
	    (!on && !(rs->opts & RS_OPT_SVC_ACTIVE)))
		return 0;

	if (on) {
		if (!rs->keepalive_time) {
			if ((f = fopen("/proc/sys/net/ipv4/tcp_keepalive_time", "r"))) {
				if (fscanf(f, "%u", &rs->keepalive_time) != 1)
					rs->keepalive_time = 7200;
				fclose(f);
			} else {
				rs->keepalive_time = 7200;
			}
		}
		ret = rs_notify_svc(&tcp_svc, rs, RS_SVC_ADD_KEEPALIVE);
	} else {
		ret = rs_notify_svc(&tcp_svc, rs, RS_SVC_REM_KEEPALIVE);
	}

	return ret;
}
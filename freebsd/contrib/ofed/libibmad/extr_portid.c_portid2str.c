#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ cnt; } ;
struct TYPE_4__ {int lid; TYPE_3__ drpath; int /*<<< orphan*/  gid; scalar_t__ grh_present; } ;
typedef  TYPE_1__ ib_portid_t ;
typedef  int /*<<< orphan*/  gid ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  drpath2str (TYPE_3__*,char*,int) ; 
 scalar_t__ inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ sprintf (char*,char*,...) ; 

char *portid2str(ib_portid_t * portid)
{
	static char buf[1024] = "local";
	int n = 0;

	if (portid->lid > 0) {
		n += sprintf(buf + n, "Lid %d", portid->lid);
		if (portid->grh_present) {
			char gid[sizeof
				 "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"];
			if (inet_ntop(AF_INET6, portid->gid, gid, sizeof(gid)))
				n += sprintf(buf + n, " Gid %s", gid);
		}
		if (portid->drpath.cnt)
			n += sprintf(buf + n, " ");
		else
			return buf;
	}
	n += sprintf(buf + n, "DR path ");
	drpath2str(&(portid->drpath), buf + n, sizeof(buf) - n);

	return buf;
}
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
struct lagg_reqopts {int ro_opts; int /*<<< orphan*/  ro_ifname; } ;
struct afswtch {int dummy; } ;
typedef  int /*<<< orphan*/  ro ;

/* Variables and functions */
#define  LAGG_OPT_LACP_RXTEST 133 
#define  LAGG_OPT_LACP_STRICT 132 
#define  LAGG_OPT_LACP_TIMEOUT 131 
#define  LAGG_OPT_LACP_TXTEST 130 
#define  LAGG_OPT_USE_FLOWID 129 
#define  LAGG_OPT_USE_NUMA 128 
 int /*<<< orphan*/  SIOCSLAGGOPTS ; 
 int /*<<< orphan*/  bzero (struct lagg_reqopts*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct lagg_reqopts*) ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
setlaggsetopt(const char *val, int d, int s, const struct afswtch *afp)
{
	struct lagg_reqopts ro;

	bzero(&ro, sizeof(ro));
	ro.ro_opts = d;
	switch (ro.ro_opts) {
	case LAGG_OPT_USE_FLOWID:
	case -LAGG_OPT_USE_FLOWID:
	case LAGG_OPT_USE_NUMA:
	case -LAGG_OPT_USE_NUMA:
	case LAGG_OPT_LACP_STRICT:
	case -LAGG_OPT_LACP_STRICT:
	case LAGG_OPT_LACP_TXTEST:
	case -LAGG_OPT_LACP_TXTEST:
	case LAGG_OPT_LACP_RXTEST:
	case -LAGG_OPT_LACP_RXTEST:
	case LAGG_OPT_LACP_TIMEOUT:
	case -LAGG_OPT_LACP_TIMEOUT:
		break;
	default:
		err(1, "Invalid lagg option");
	}
	strlcpy(ro.ro_ifname, name, sizeof(ro.ro_ifname));
	
	if (ioctl(s, SIOCSLAGGOPTS, &ro) != 0)
		err(1, "SIOCSLAGGOPTS");
}
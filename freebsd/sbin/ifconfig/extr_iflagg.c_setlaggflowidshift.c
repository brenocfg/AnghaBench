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
struct lagg_reqopts {int ro_flowid_shift; int /*<<< orphan*/  ro_ifname; int /*<<< orphan*/  ro_opts; } ;
struct afswtch {int dummy; } ;
typedef  int /*<<< orphan*/  ro ;

/* Variables and functions */
 int /*<<< orphan*/  LAGG_OPT_FLOWIDSHIFT ; 
 int LAGG_OPT_FLOWIDSHIFT_MASK ; 
 int /*<<< orphan*/  SIOCSLAGGOPTS ; 
 int /*<<< orphan*/  bzero (struct lagg_reqopts*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct lagg_reqopts*) ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strtol (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
setlaggflowidshift(const char *val, int d, int s, const struct afswtch *afp)
{
	struct lagg_reqopts ro;

	bzero(&ro, sizeof(ro));
	ro.ro_opts = LAGG_OPT_FLOWIDSHIFT;
	strlcpy(ro.ro_ifname, name, sizeof(ro.ro_ifname));
	ro.ro_flowid_shift = (int)strtol(val, NULL, 10);
	if (ro.ro_flowid_shift & ~LAGG_OPT_FLOWIDSHIFT_MASK)
		errx(1, "Invalid flowid_shift option: %s", val);
	
	if (ioctl(s, SIOCSLAGGOPTS, &ro) != 0)
		err(1, "SIOCSLAGGOPTS");
}
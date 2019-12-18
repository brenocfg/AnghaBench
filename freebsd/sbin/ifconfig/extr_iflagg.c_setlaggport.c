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
struct lagg_reqport {int /*<<< orphan*/  rp_portname; int /*<<< orphan*/  rp_ifname; } ;
struct afswtch {int dummy; } ;
typedef  int /*<<< orphan*/  rp ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  SIOCSLAGGPORT ; 
 int /*<<< orphan*/  bzero (struct lagg_reqport*,int) ; 
 scalar_t__ errno ; 
 int exit_code ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct lagg_reqport*) ; 
 char const* name ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  warnx (char*,char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
setlaggport(const char *val, int d, int s, const struct afswtch *afp)
{
	struct lagg_reqport rp;

	bzero(&rp, sizeof(rp));
	strlcpy(rp.rp_ifname, name, sizeof(rp.rp_ifname));
	strlcpy(rp.rp_portname, val, sizeof(rp.rp_portname));

	/*
	 * Do not exit with an error here.  Doing so permits a
	 * failed NIC to take down an entire lagg.
	 *
	 * Don't error at all if the port is already in the lagg.
	 */
	if (ioctl(s, SIOCSLAGGPORT, &rp) && errno != EEXIST) {
		warnx("%s %s: SIOCSLAGGPORT: %s",
		    name, val, strerror(errno));
		exit_code = 1;
	}
}
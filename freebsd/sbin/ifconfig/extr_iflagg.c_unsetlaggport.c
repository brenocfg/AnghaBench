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
 int /*<<< orphan*/  SIOCSLAGGDELPORT ; 
 int /*<<< orphan*/  bzero (struct lagg_reqport*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct lagg_reqport*) ; 
 char const* name ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
unsetlaggport(const char *val, int d, int s, const struct afswtch *afp)
{
	struct lagg_reqport rp;

	bzero(&rp, sizeof(rp));
	strlcpy(rp.rp_ifname, name, sizeof(rp.rp_ifname));
	strlcpy(rp.rp_portname, val, sizeof(rp.rp_portname));

	if (ioctl(s, SIOCSLAGGDELPORT, &rp))
		err(1, "SIOCSLAGGDELPORT");
}
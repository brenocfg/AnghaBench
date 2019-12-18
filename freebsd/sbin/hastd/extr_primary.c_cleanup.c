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
struct hast_resource {int hr_ggateunit; int /*<<< orphan*/  hr_provname; int /*<<< orphan*/  hr_ggatefd; } ;
struct g_gate_ctl_destroy {int gctl_unit; int gctl_force; int /*<<< orphan*/  gctl_version; } ;
typedef  int /*<<< orphan*/  ggiod ;

/* Variables and functions */
 int /*<<< orphan*/  G_GATE_CMD_DESTROY ; 
 int /*<<< orphan*/  G_GATE_VERSION ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  bzero (struct g_gate_ctl_destroy*,int) ; 
 int errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct g_gate_ctl_destroy*) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cleanup(struct hast_resource *res)
{
	int rerrno;

	/* Remember errno. */
	rerrno = errno;

	/* Destroy ggate provider if we created one. */
	if (res->hr_ggateunit >= 0) {
		struct g_gate_ctl_destroy ggiod;

		bzero(&ggiod, sizeof(ggiod));
		ggiod.gctl_version = G_GATE_VERSION;
		ggiod.gctl_unit = res->hr_ggateunit;
		ggiod.gctl_force = 1;
		if (ioctl(res->hr_ggatefd, G_GATE_CMD_DESTROY, &ggiod) == -1) {
			pjdlog_errno(LOG_WARNING,
			    "Unable to destroy hast/%s device",
			    res->hr_provname);
		}
		res->hr_ggateunit = -1;
	}

	/* Restore errno. */
	errno = rerrno;
}
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
struct sc_info {int /*<<< orphan*/  spdif_enabled; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RW ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmi_initsys(struct sc_info* sc)
{
	/* XXX: an user should be able to set this with a control tool,
	   if not done before 7.0-RELEASE, this needs to be converted
	   to a device specific sysctl "dev.pcm.X.yyy" via
	   device_get_sysctl_*() as discussed on multimedia@ in msg-id
	   <861wujij2q.fsf@xps.des.no> */
	SYSCTL_ADD_INT(device_get_sysctl_ctx(sc->dev), 
		       SYSCTL_CHILDREN(device_get_sysctl_tree(sc->dev)),
		       OID_AUTO, "spdif_enabled", CTLFLAG_RW, 
		       &sc->spdif_enabled, 0, 
		       "enable SPDIF output at 44.1 kHz and above");

	return 0;
}
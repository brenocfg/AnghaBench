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
struct ucred {int dummy; } ;
struct tuntap_driver {int /*<<< orphan*/  cdevsw; int /*<<< orphan*/  clones; } ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  devname ;

/* Variables and functions */
 int /*<<< orphan*/  CRED_TO_VNET (struct ucred*) ; 
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int IF_MAXUNIT ; 
 int /*<<< orphan*/  PRIV_NET_IFCREATE ; 
 int /*<<< orphan*/  SPECNAMELEN ; 
 int TUN_L2 ; 
 int clone_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,struct cdev**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_clone_create (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char*,int) ; 
 scalar_t__ tap_allow_uopen ; 
 scalar_t__ tapdclone ; 
 int tun_create_device (struct tuntap_driver*,int,struct ucred*,struct cdev**,char*) ; 
 scalar_t__ tundclone ; 
 struct tuntap_driver* tuntap_driver_from_flags (int) ; 
 scalar_t__ tuntap_name2info (char*,int*,int*) ; 

__attribute__((used)) static void
tunclone(void *arg, struct ucred *cred, char *name, int namelen,
    struct cdev **dev)
{
	char devname[SPECNAMELEN + 1];
	struct tuntap_driver *drv;
	int append_unit, i, u, tunflags;
	bool mayclone;

	if (*dev != NULL)
		return;

	tunflags = 0;
	CURVNET_SET(CRED_TO_VNET(cred));
	if (tuntap_name2info(name, &u, &tunflags) != 0)
		goto out;	/* Not recognized */

	if (u != -1 && u > IF_MAXUNIT)
		goto out;	/* Unit number too high */

	mayclone = priv_check_cred(cred, PRIV_NET_IFCREATE) == 0;
	if ((tunflags & TUN_L2) != 0) {
		/* tap/vmnet allow user open with a sysctl */
		mayclone = (mayclone || tap_allow_uopen) && tapdclone;
	} else {
		mayclone = mayclone && tundclone;
	}

	/*
	 * If tun cloning is enabled, only the superuser can create an
	 * interface.
	 */
	if (!mayclone)
		goto out;

	if (u == -1)
		append_unit = 1;
	else
		append_unit = 0;

	drv = tuntap_driver_from_flags(tunflags);
	if (drv == NULL)
		goto out;

	/* find any existing device, or allocate new unit number */
	i = clone_create(&drv->clones, &drv->cdevsw, &u, dev, 0);
	if (i) {
		if (append_unit) {
			namelen = snprintf(devname, sizeof(devname), "%s%d",
			    name, u);
			name = devname;
		}

		i = tun_create_device(drv, u, cred, dev, name);
	}
	if (i == 0)
		if_clone_create(name, namelen, NULL);
out:
	CURVNET_RESTORE();
}
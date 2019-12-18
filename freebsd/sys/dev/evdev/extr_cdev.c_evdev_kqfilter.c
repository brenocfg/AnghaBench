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
struct knote {int kn_filter; scalar_t__ kn_hook; int /*<<< orphan*/ * kn_fop; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct evdev_client {TYPE_1__ ec_selp; scalar_t__ ec_revoked; } ;
struct cdev {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
#define  EVFILT_READ 128 
 int devfs_get_cdevpriv (void**) ; 
 int /*<<< orphan*/  evdev_cdev_filterops ; 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
evdev_kqfilter(struct cdev *dev, struct knote *kn)
{
	struct evdev_client *client;
	int ret;

	ret = devfs_get_cdevpriv((void **)&client);
	if (ret != 0)
		return (ret);

	if (client->ec_revoked)
		return (ENODEV);

	switch(kn->kn_filter) {
	case EVFILT_READ:
		kn->kn_fop = &evdev_cdev_filterops;
		break;
	default:
		return(EINVAL);
	}
	kn->kn_hook = (caddr_t)client;

	knlist_add(&client->ec_selp.si_note, kn, 0);
	return (0);
}
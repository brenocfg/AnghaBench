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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct uinput_cdev_state {TYPE_1__ ucs_selp; } ;
struct knote {int kn_filter; scalar_t__ kn_hook; int /*<<< orphan*/ * kn_fop; } ;
struct cdev {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
#define  EVFILT_READ 128 
 int devfs_get_cdevpriv (void**) ; 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uinput_filterops ; 

__attribute__((used)) static int
uinput_kqfilter(struct cdev *dev, struct knote *kn)
{
	struct uinput_cdev_state *state;
	int ret;

	ret = devfs_get_cdevpriv((void **)&state);
	if (ret != 0)
		return (ret);

	switch(kn->kn_filter) {
	case EVFILT_READ:
		kn->kn_fop = &uinput_filterops;
		break;
	default:
		return(EINVAL);
	}
	kn->kn_hook = (caddr_t)state;

	knlist_add(&state->ucs_selp.si_note, kn, 0);
	return (0);
}
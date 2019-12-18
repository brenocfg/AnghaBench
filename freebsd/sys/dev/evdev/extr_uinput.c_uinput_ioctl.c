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
typedef  int /*<<< orphan*/  u_long ;
struct uinput_cdev_state {int dummy; } ;
struct thread {int dummy; } ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  UINPUT_LOCK (struct uinput_cdev_state*) ; 
 int /*<<< orphan*/  UINPUT_UNLOCK (struct uinput_cdev_state*) ; 
 int /*<<< orphan*/  debugf (struct uinput_cdev_state*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devfs_get_cdevpriv (void**) ; 
 int uinput_ioctl_sub (struct uinput_cdev_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uinput_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int fflag,
    struct thread *td)
{
	struct uinput_cdev_state *state;
	int ret;

	ret = devfs_get_cdevpriv((void **)&state);
	if (ret != 0)
		return (ret);

	debugf(state, "ioctl called: cmd=0x%08lx, data=%p", cmd, data);

	UINPUT_LOCK(state);
	ret = uinput_ioctl_sub(state, cmd, data);
	UINPUT_UNLOCK(state);

	return (ret);
}
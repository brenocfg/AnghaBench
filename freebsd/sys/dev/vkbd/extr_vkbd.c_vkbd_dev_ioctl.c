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
struct thread {int dummy; } ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  keyboard_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/ * VKBD_KEYBOARD (struct cdev*) ; 
 int kbdd_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vkbd_dev_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int flag, struct thread *td)
{
	keyboard_t	*kbd = VKBD_KEYBOARD(dev);

	return ((kbd == NULL)? ENXIO : kbdd_ioctl(kbd, cmd, data));
}
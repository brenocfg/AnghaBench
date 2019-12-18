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
struct vt_device {int vd_keyboard; } ;
typedef  int /*<<< orphan*/  keyboard_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  Giant ; 
#define  KBDIO_KEYINPUT 129 
#define  KBDIO_UNLOADING 128 
 int NOKEY ; 
 int /*<<< orphan*/  kbd_release (int /*<<< orphan*/ *,void*) ; 
 int kbdd_read_char (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vt_processkey (int /*<<< orphan*/ *,struct vt_device*,int) ; 

__attribute__((used)) static int
vt_kbdevent(keyboard_t *kbd, int event, void *arg)
{
	struct vt_device *vd = arg;
	int c;

	switch (event) {
	case KBDIO_KEYINPUT:
		break;
	case KBDIO_UNLOADING:
		mtx_lock(&Giant);
		vd->vd_keyboard = -1;
		kbd_release(kbd, (void *)vd);
		mtx_unlock(&Giant);
		return (0);
	default:
		return (EINVAL);
	}

	while ((c = kbdd_read_char(kbd, 0)) != NOKEY)
		vt_processkey(kbd, vd, c);

	return (0);
}
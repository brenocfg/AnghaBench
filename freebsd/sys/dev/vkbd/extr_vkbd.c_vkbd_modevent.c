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
typedef  int /*<<< orphan*/  module_t ;
typedef  int /*<<< orphan*/ * eventhandler_tag ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  clone_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clone_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_clone ; 
 int /*<<< orphan*/  kbd_add_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kbd_delete_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkbd_dev_clone ; 
 int /*<<< orphan*/  vkbd_dev_clones ; 
 int /*<<< orphan*/  vkbd_kbd_driver ; 

__attribute__((used)) static int
vkbd_modevent(module_t mod, int type, void *data)
{
	static eventhandler_tag	tag;

	switch (type) {
	case MOD_LOAD:
		clone_setup(&vkbd_dev_clones);
		tag = EVENTHANDLER_REGISTER(dev_clone, vkbd_dev_clone, 0, 1000);
		if (tag == NULL) {
			clone_cleanup(&vkbd_dev_clones);
			return (ENOMEM);
		}
		kbd_add_driver(&vkbd_kbd_driver);
		break;

	case MOD_UNLOAD:
		kbd_delete_driver(&vkbd_kbd_driver);
		EVENTHANDLER_DEREGISTER(dev_clone, tag);
		clone_cleanup(&vkbd_dev_clones);
		break;

	default:
		return (EOPNOTSUPP);
	}

	return (0);
}
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

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  akbd_kbd_driver ; 
 int /*<<< orphan*/  kbd_add_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kbd_delete_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
akbd_modevent(module_t mod, int type, void *data)
{
	switch (type) {
	case MOD_LOAD:
		kbd_add_driver(&akbd_kbd_driver);
		break;

	case MOD_UNLOAD:
		kbd_delete_driver(&akbd_kbd_driver);
		break;

	default:
		return (EOPNOTSUPP);
	}

	return (0);
}
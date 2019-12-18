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
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int qlnxr_mod_load () ; 
 int qlnxr_mod_unload () ; 

__attribute__((used)) static int
qlnxr_event_handler(module_t mod, int event, void *arg)
{

	int ret = 0;

	switch (event) {

	case MOD_LOAD:
		ret = qlnxr_mod_load();
		break;

	case MOD_UNLOAD:
		ret = qlnxr_mod_unload();
		break;

	default:
		break;
	}

        return (ret);
}
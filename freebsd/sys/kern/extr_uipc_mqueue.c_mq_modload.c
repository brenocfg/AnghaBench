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
struct module {int dummy; } ;

/* Variables and functions */
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int mqinit () ; 
 int mqunload () ; 
 int vfs_modevent (struct module*,int,void*) ; 

__attribute__((used)) static int
mq_modload(struct module *module, int cmd, void *arg)
{
	int error = 0;

	error = vfs_modevent(module, cmd, arg);
	if (error != 0)
		return (error);

	switch (cmd) {
	case MOD_LOAD:
		error = mqinit();
		if (error != 0)
			mqunload();
		break;
	case MOD_UNLOAD:
		error = mqunload();
		break;
	default:
		break;
	}
	return (error);
}
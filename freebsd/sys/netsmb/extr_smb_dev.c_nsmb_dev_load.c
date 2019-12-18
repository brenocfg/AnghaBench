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
 int EINVAL ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  nsmb_dev_destroy () ; 
 int nsmb_dev_init () ; 
 int /*<<< orphan*/  smb_iod_done () ; 
 int smb_iod_init () ; 
 int /*<<< orphan*/  smb_lock ; 
 int smb_sm_done () ; 
 int smb_sm_init () ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
nsmb_dev_load(module_t mod, int cmd, void *arg)
{
	int error = 0;

	switch (cmd) {
	    case MOD_LOAD:
		error = smb_sm_init();
		if (error)
			break;
		error = smb_iod_init();
		if (error) {
			smb_sm_done();
			break;
		}
		error = nsmb_dev_init();
		if (error)
			break;
		sx_init(&smb_lock, "samba device lock");
		break;
	    case MOD_UNLOAD:
		smb_iod_done();
		error = smb_sm_done();
		if (error)
			break;
		nsmb_dev_destroy();
		sx_destroy(&smb_lock);
		break;
	    default:
		error = EINVAL;
		break;
	}
	return error;
}
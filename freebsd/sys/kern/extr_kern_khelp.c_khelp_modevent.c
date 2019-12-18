#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct khelp_modevent_data {char* name; TYPE_1__* helper; int /*<<< orphan*/  nhooks; int /*<<< orphan*/  hooks; int /*<<< orphan*/  umadtor; int /*<<< orphan*/  umactor; int /*<<< orphan*/  uma_zsize; } ;
typedef  int /*<<< orphan*/  module_t ;
struct TYPE_3__ {int h_flags; int (* mod_init ) () ;int h_refcount; int /*<<< orphan*/  (* mod_destroy ) () ;int /*<<< orphan*/ * h_zone; int /*<<< orphan*/  h_nhooks; int /*<<< orphan*/  h_hooks; int /*<<< orphan*/  h_name; } ;

/* Variables and functions */
 int EBUSY ; 
 int EDOOFUS ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HELPER_NAME_MAXLEN ; 
 int HELPER_NEEDS_OSD ; 
#define  MOD_LOAD 131 
#define  MOD_QUIESCE 130 
#define  MOD_SHUTDOWN 129 
#define  MOD_UNLOAD 128 
 int khelp_deregister_helper (TYPE_1__*) ; 
 int khelp_register_helper (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/ * uma_zcreate (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ *) ; 

int
khelp_modevent(module_t mod, int event_type, void *data)
{
	struct khelp_modevent_data *kmd;
	int error;

	kmd = (struct khelp_modevent_data *)data;
	error = 0;

	switch(event_type) {
	case MOD_LOAD:
		if (kmd->helper->h_flags & HELPER_NEEDS_OSD) {
			if (kmd->uma_zsize <= 0) {
				printf("Use KHELP_DECLARE_MOD_UMA() instead!\n");
				error = EDOOFUS;
				break;
			}
			kmd->helper->h_zone = uma_zcreate(kmd->name,
			    kmd->uma_zsize, kmd->umactor, kmd->umadtor, NULL,
			    NULL, 0, 0);
			if (kmd->helper->h_zone == NULL) {
				error = ENOMEM;
				break;
			}
		}
		strlcpy(kmd->helper->h_name, kmd->name, HELPER_NAME_MAXLEN);
		kmd->helper->h_hooks = kmd->hooks;
		kmd->helper->h_nhooks = kmd->nhooks;
		if (kmd->helper->mod_init != NULL)
			error = kmd->helper->mod_init();
		if (!error)
			error = khelp_register_helper(kmd->helper);
		break;

	case MOD_QUIESCE:
	case MOD_SHUTDOWN:
	case MOD_UNLOAD:
		error = khelp_deregister_helper(kmd->helper);
		if (!error) {
			if (kmd->helper->h_flags & HELPER_NEEDS_OSD)
				uma_zdestroy(kmd->helper->h_zone);
			if (kmd->helper->mod_destroy != NULL)
				kmd->helper->mod_destroy();
		} else if (error == ENOENT)
			/* Do nothing and allow unload if helper not in list. */
			error = 0;
		else if (error == EBUSY)
			printf("Khelp module \"%s\" can't unload until its "
			    "refcount drops from %d to 0.\n", kmd->name,
			    kmd->helper->h_refcount);
		break;

	default:
		error = EINVAL;
		break;
	}

	return (error);
}
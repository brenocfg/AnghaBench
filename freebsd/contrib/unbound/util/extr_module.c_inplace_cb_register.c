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
struct module_env {int /*<<< orphan*/ * inplace_cb_lists; scalar_t__ worker; } ;
struct inplace_cb {int id; struct inplace_cb* next; void* cb_arg; void* cb; } ;
typedef  enum inplace_cb_list_type { ____Placeholder_inplace_cb_list_type } inplace_cb_list_type ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  log_err (char*) ; 

int
inplace_cb_register(void* cb, enum inplace_cb_list_type type, void* cbarg,
	struct module_env* env, int id)
{
	struct inplace_cb* callback;
	struct inplace_cb** prevp;
	if(env->worker) {
		log_err("invalid edns callback registration: "
			"trying to register callback after module init phase");
		return 0;
	}

	callback = (struct inplace_cb*)calloc(1, sizeof(*callback));
	if(callback == NULL) {
		log_err("out of memory during edns callback registration.");
		return 0;
	}
	callback->id = id;
	callback->next = NULL;
	callback->cb = cb;
	callback->cb_arg = cbarg;
	
	prevp = (struct inplace_cb**) &env->inplace_cb_lists[type];
	/* append at end of list */
	while(*prevp != NULL)
		prevp = &((*prevp)->next);
	*prevp = callback;
	return 1;
}
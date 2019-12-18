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
struct evrpc_hook_list {int dummy; } ;
struct evrpc_hooks_ {struct evrpc_hook_list out_hooks; struct evrpc_hook_list in_hooks; } ;
typedef  enum EVRPC_HOOK_TYPE { ____Placeholder_EVRPC_HOOK_TYPE } EVRPC_HOOK_TYPE ;

/* Variables and functions */
#define  EVRPC_INPUT 129 
#define  EVRPC_OUTPUT 128 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int evrpc_remove_hook_internal (struct evrpc_hook_list*,void*) ; 

int
evrpc_remove_hook(void *vbase, enum EVRPC_HOOK_TYPE hook_type, void *handle)
{
	struct evrpc_hooks_ *base = vbase;
	struct evrpc_hook_list *head = NULL;
	switch (hook_type) {
	case EVRPC_INPUT:
		head = &base->in_hooks;
		break;
	case EVRPC_OUTPUT:
		head = &base->out_hooks;
		break;
	default:
		EVUTIL_ASSERT(hook_type == EVRPC_INPUT || hook_type == EVRPC_OUTPUT);
	}

	return (evrpc_remove_hook_internal(head, handle));
}
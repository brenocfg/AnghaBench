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
struct sysent {int dummy; } ;
struct syscall_module_data {int (* chainevh ) (struct module*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  chainarg; int /*<<< orphan*/  old_sysent; int /*<<< orphan*/ * offset; int /*<<< orphan*/  flags; int /*<<< orphan*/  new_sysent; } ;
struct module {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  intval; } ;
typedef  TYPE_1__ modspecific_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  MOD_XLOCK ; 
 int /*<<< orphan*/  MOD_XUNLOCK ; 
 int kern_syscall_deregister (struct sysent*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kern_syscall_register (struct sysent*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_setspecific (struct module*,TYPE_1__*) ; 
 int stub1 (struct module*,int,int /*<<< orphan*/ ) ; 
 int stub2 (struct module*,int,int /*<<< orphan*/ ) ; 
 int stub3 (struct module*,int,int /*<<< orphan*/ ) ; 

int
kern_syscall_module_handler(struct sysent *sysents, struct module *mod,
    int what, void *arg)
{
	struct syscall_module_data *data = arg;
	modspecific_t ms;
	int error;

	switch (what) {
	case MOD_LOAD:
		error = kern_syscall_register(sysents, data->offset,
		    data->new_sysent, &data->old_sysent, data->flags);
		if (error) {
			/* Leave a mark so we know to safely unload below. */
			data->offset = NULL;
			return (error);
		}
		ms.intval = *data->offset;
		MOD_XLOCK;
		module_setspecific(mod, &ms);
		MOD_XUNLOCK;
		if (data->chainevh)
			error = data->chainevh(mod, what, data->chainarg);
		return (error);
	case MOD_UNLOAD:
		/*
		 * MOD_LOAD failed, so just return without calling the
		 * chained handler since we didn't pass along the MOD_LOAD
		 * event.
		 */
		if (data->offset == NULL)
			return (0);
		if (data->chainevh) {
			error = data->chainevh(mod, what, data->chainarg);
			if (error)
				return error;
		}
		error = kern_syscall_deregister(sysents, *data->offset,
		    &data->old_sysent);
		return (error);
	default:
		if (data->chainevh)
			return (data->chainevh(mod, what, data->chainarg));
		return (EOPNOTSUPP);
	}

	/* NOTREACHED */
}
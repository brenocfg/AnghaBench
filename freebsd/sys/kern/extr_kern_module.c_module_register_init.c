#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* name; int /*<<< orphan*/  priv; scalar_t__ evhand; } ;
typedef  TYPE_2__ moduledata_t ;
typedef  TYPE_3__* module_t ;
struct TYPE_11__ {TYPE_1__* file; } ;
struct TYPE_9__ {int /*<<< orphan*/  modules; } ;

/* Variables and functions */
 int /*<<< orphan*/  Giant ; 
 int MOD_EVENT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MOD_LOAD ; 
 int /*<<< orphan*/  MOD_SLOCK ; 
 int /*<<< orphan*/  MOD_SUNLOCK ; 
 int /*<<< orphan*/  MOD_UNLOAD ; 
 int /*<<< orphan*/  MOD_XLOCK ; 
 int /*<<< orphan*/  MOD_XUNLOCK ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flink ; 
 TYPE_3__* module_lookupbyname (char*) ; 
 int /*<<< orphan*/  module_release (TYPE_3__*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*,void*,int /*<<< orphan*/ ,int) ; 

void
module_register_init(const void *arg)
{
	const moduledata_t *data = (const moduledata_t *)arg;
	int error;
	module_t mod;

	mtx_lock(&Giant);
	MOD_SLOCK;
	mod = module_lookupbyname(data->name);
	if (mod == NULL)
		panic("module_register_init: module named %s not found\n",
		    data->name);
	MOD_SUNLOCK;
	error = MOD_EVENT(mod, MOD_LOAD);
	if (error) {
		MOD_EVENT(mod, MOD_UNLOAD);
		MOD_XLOCK;
		module_release(mod);
		MOD_XUNLOCK;
		printf("module_register_init: MOD_LOAD (%s, %p, %p) error"
		    " %d\n", data->name, (void *)data->evhand, data->priv,
		    error); 
	} else {
		MOD_XLOCK;
		if (mod->file) {
			/*
			 * Once a module is successfully loaded, move
			 * it to the head of the module list for this
			 * linker file.  This resorts the list so that
			 * when the kernel linker iterates over the
			 * modules to unload them, it will unload them
			 * in the reverse order they were loaded.
			 */
			TAILQ_REMOVE(&mod->file->modules, mod, flink);
			TAILQ_INSERT_HEAD(&mod->file->modules, mod, flink);
		}
		MOD_XUNLOCK;
	}
	mtx_unlock(&Giant);
}
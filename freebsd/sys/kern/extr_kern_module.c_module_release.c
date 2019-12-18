#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* module_t ;
struct TYPE_7__ {scalar_t__ refs; TYPE_1__* file; } ;
struct TYPE_6__ {int /*<<< orphan*/  modules; } ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_DPF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MOD_XLOCK_ASSERT ; 
 int /*<<< orphan*/  M_MODULE ; 
 int /*<<< orphan*/  REFS ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flink ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  modules ; 
 int /*<<< orphan*/  panic (char*) ; 

void
module_release(module_t mod)
{

	MOD_XLOCK_ASSERT;

	if (mod->refs <= 0)
		panic("module_release: bad reference count");

	MOD_DPF(REFS, ("module_release: before, refs=%d\n", mod->refs));
	
	mod->refs--;
	if (mod->refs == 0) {
		TAILQ_REMOVE(&modules, mod, link);
		if (mod->file)
			TAILQ_REMOVE(&mod->file->modules, mod, flink);
		free(mod, M_MODULE);
	}
}
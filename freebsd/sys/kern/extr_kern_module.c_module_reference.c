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
typedef  TYPE_1__* module_t ;
struct TYPE_3__ {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_DPF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MOD_XLOCK_ASSERT ; 
 int /*<<< orphan*/  REFS ; 

void
module_reference(module_t mod)
{

	MOD_XLOCK_ASSERT;

	MOD_DPF(REFS, ("module_reference: before, refs=%d\n", mod->refs));
	mod->refs++;
}
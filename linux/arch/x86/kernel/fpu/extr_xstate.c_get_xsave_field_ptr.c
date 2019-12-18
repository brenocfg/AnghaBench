#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  xsave; } ;
struct fpu {TYPE_2__ state; } ;
struct TYPE_4__ {struct fpu fpu; } ;
struct TYPE_6__ {TYPE_1__ thread; } ;

/* Variables and functions */
 TYPE_3__* current ; 
 int /*<<< orphan*/  fpu__save (struct fpu*) ; 
 void const* get_xsave_addr (int /*<<< orphan*/ *,int) ; 

const void *get_xsave_field_ptr(int xfeature_nr)
{
	struct fpu *fpu = &current->thread.fpu;

	/*
	 * fpu__save() takes the CPU's xstate registers
	 * and saves them off to the 'fpu memory buffer.
	 */
	fpu__save(fpu);

	return get_xsave_addr(&fpu->state.xsave, xfeature_nr);
}
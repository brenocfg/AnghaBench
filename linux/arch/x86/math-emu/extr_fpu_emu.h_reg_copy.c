#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sigl; int /*<<< orphan*/  exp; } ;
typedef  TYPE_1__ FPU_REG ;

/* Variables and functions */

__attribute__((used)) static inline void reg_copy(FPU_REG const *x, FPU_REG *y)
{
	*(short *)&(y->exp) = *(const short *)&(x->exp);
	*(long long *)&(y->sigl) = *(const long long *)&(x->sigl);
}
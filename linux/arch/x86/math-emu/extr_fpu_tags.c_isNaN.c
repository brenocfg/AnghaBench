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
struct TYPE_4__ {int sigh; scalar_t__ sigl; } ;
typedef  TYPE_1__ FPU_REG ;

/* Variables and functions */
 scalar_t__ EXP_BIAS ; 
 scalar_t__ EXP_OVER ; 
 scalar_t__ exponent (TYPE_1__ const*) ; 

int isNaN(FPU_REG const *ptr)
{
	return ((exponent(ptr) == EXP_BIAS + EXP_OVER)
		&& !((ptr->sigh == 0x80000000) && (ptr->sigl == 0)));
}
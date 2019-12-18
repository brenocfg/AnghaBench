#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int dummy; } ;
struct TYPE_2__ {scalar_t__ ia32_compat; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 scalar_t__ NONE ; 
 struct vm_area_struct gate_vma ; 
 scalar_t__ vsyscall_mode ; 

struct vm_area_struct *get_gate_vma(struct mm_struct *mm)
{
#ifdef CONFIG_COMPAT
	if (!mm || mm->context.ia32_compat)
		return NULL;
#endif
	if (vsyscall_mode == NONE)
		return NULL;
	return &gate_vma;
}
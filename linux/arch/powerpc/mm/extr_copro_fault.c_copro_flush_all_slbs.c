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
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxl_slbia (struct mm_struct*) ; 
 int /*<<< orphan*/  spu_flush_all_slbs (struct mm_struct*) ; 

void copro_flush_all_slbs(struct mm_struct *mm)
{
#ifdef CONFIG_SPU_BASE
	spu_flush_all_slbs(mm);
#endif
	cxl_slbia(mm);
}
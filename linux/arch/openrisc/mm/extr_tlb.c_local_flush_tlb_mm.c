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
 int /*<<< orphan*/  local_flush_tlb_all () ; 

void local_flush_tlb_mm(struct mm_struct *mm)
{

	/* Was seeing bugs with the mm struct passed to us. Scrapped most of
	   this function. */
	/* Several architctures do this */
	local_flush_tlb_all();
}
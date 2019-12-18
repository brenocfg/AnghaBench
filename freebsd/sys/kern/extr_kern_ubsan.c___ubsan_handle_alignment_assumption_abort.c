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
struct CAlignmentAssumptionData {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct CAlignmentAssumptionData*) ; 
 int /*<<< orphan*/  HandleAlignmentAssumption (int,struct CAlignmentAssumptionData*,unsigned long,unsigned long,unsigned long) ; 

void
__ubsan_handle_alignment_assumption_abort(struct CAlignmentAssumptionData *pData, unsigned long ulPointer, unsigned long ulAlignment, unsigned long ulOffset)
{

	ASSERT(pData);

	HandleAlignmentAssumption(true, pData, ulPointer, ulAlignment, ulOffset);
}
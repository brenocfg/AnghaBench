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
struct CShiftOutOfBoundsData {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct CShiftOutOfBoundsData*) ; 
 int /*<<< orphan*/  HandleShiftOutOfBounds (int,struct CShiftOutOfBoundsData*,unsigned long,unsigned long) ; 

void
__ubsan_handle_shift_out_of_bounds(struct CShiftOutOfBoundsData *pData, unsigned long ulLHS, unsigned long ulRHS)
{

	ASSERT(pData);

	HandleShiftOutOfBounds(false, pData, ulLHS, ulRHS);
}
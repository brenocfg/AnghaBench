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
struct COutOfBoundsData {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct COutOfBoundsData*) ; 
 int /*<<< orphan*/  HandleOutOfBounds (int,struct COutOfBoundsData*,unsigned long) ; 

void
__ubsan_handle_out_of_bounds(struct COutOfBoundsData *pData, unsigned long ulIndex)
{

	ASSERT(pData);

	HandleOutOfBounds(false, pData, ulIndex);
}
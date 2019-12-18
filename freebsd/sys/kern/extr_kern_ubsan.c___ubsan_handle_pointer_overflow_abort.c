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
struct CPointerOverflowData {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct CPointerOverflowData*) ; 
 int /*<<< orphan*/  HandlePointerOverflow (int,struct CPointerOverflowData*,unsigned long,unsigned long) ; 

void
__ubsan_handle_pointer_overflow_abort(struct CPointerOverflowData *pData, unsigned long ulBase, unsigned long ulResult)
{

	ASSERT(pData);

	HandlePointerOverflow(true, pData, ulBase, ulResult);
}
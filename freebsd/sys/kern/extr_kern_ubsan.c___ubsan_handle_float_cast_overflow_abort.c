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
struct CFloatCastOverflowData {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct CFloatCastOverflowData*) ; 
 int /*<<< orphan*/  HandleFloatCastOverflow (int,struct CFloatCastOverflowData*,unsigned long) ; 

void
__ubsan_handle_float_cast_overflow_abort(struct CFloatCastOverflowData *pData, unsigned long ulFrom)
{

	ASSERT(pData);

	HandleFloatCastOverflow(true, pData, ulFrom);
}
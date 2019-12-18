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
struct CVLABoundData {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct CVLABoundData*) ; 
 int /*<<< orphan*/  HandleVlaBoundNotPositive (int,struct CVLABoundData*,unsigned long) ; 

void
__ubsan_handle_vla_bound_not_positive_abort(struct CVLABoundData *pData, unsigned long ulBound)
{

	ASSERT(pData);

	HandleVlaBoundNotPositive(true, pData, ulBound);
}
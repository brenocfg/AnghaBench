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
struct CTypeMismatchData_v1 {int /*<<< orphan*/  mTypeCheckKind; int /*<<< orphan*/  mLogAlignment; int /*<<< orphan*/  mType; int /*<<< orphan*/  mLocation; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct CTypeMismatchData_v1*) ; 
 int /*<<< orphan*/  HandleTypeMismatch (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  __BIT (int /*<<< orphan*/ ) ; 

void
__ubsan_handle_type_mismatch_v1_abort(struct CTypeMismatchData_v1 *pData, unsigned long ulPointer)
{

	ASSERT(pData);

	HandleTypeMismatch(true, &pData->mLocation, pData->mType, __BIT(pData->mLogAlignment), pData->mTypeCheckKind, ulPointer);
}
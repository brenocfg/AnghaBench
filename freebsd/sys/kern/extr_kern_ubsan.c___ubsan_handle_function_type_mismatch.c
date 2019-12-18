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
struct CFunctionTypeMismatchData {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct CFunctionTypeMismatchData*) ; 
 int /*<<< orphan*/  HandleFunctionTypeMismatch (int,struct CFunctionTypeMismatchData*,unsigned long) ; 

void
__ubsan_handle_function_type_mismatch(struct CFunctionTypeMismatchData *pData, unsigned long ulFunction)
{

	ASSERT(pData);

	HandleFunctionTypeMismatch(false, pData, ulFunction);
}
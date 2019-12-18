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
struct CCFICheckFailData {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct CCFICheckFailData*) ; 
 int /*<<< orphan*/  HandleCFIBadType (int,struct CCFICheckFailData*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
__ubsan_handle_cfi_check_fail_abort(struct CCFICheckFailData *pData, unsigned long ulValue, unsigned long ulValidVtable)
{

	ASSERT(pData);

	HandleCFIBadType(true, pData, ulValue, 0, 0, 0, 0);
}
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
 int /*<<< orphan*/  HandleCFIBadType (int,struct CCFICheckFailData*,unsigned long,int*,int*,unsigned long*,unsigned long*) ; 

void
__ubsan_handle_cfi_bad_type(struct CCFICheckFailData *pData, unsigned long ulVtable, bool bValidVtable, bool FromUnrecoverableHandler, unsigned long ProgramCounter, unsigned long FramePointer)
{

	ASSERT(pData);

	HandleCFIBadType(false, pData, ulVtable, &bValidVtable, &FromUnrecoverableHandler, &ProgramCounter, &FramePointer);
}
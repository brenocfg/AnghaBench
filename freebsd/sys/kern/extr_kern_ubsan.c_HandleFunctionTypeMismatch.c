#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct CFunctionTypeMismatchData {TYPE_1__* mType; int /*<<< orphan*/  mLocation; } ;
struct TYPE_2__ {int /*<<< orphan*/  mTypeName; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct CFunctionTypeMismatchData*) ; 
 int /*<<< orphan*/  DeserializeLocation (char*,int,int /*<<< orphan*/ *) ; 
 int LOCATION_MAXLEN ; 
 int /*<<< orphan*/  Report (int,char*,char*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ isAlreadyReported (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
HandleFunctionTypeMismatch(bool isFatal, struct CFunctionTypeMismatchData *pData, unsigned long ulFunction)
{
	char szLocation[LOCATION_MAXLEN];

	/*
	 * There is no a portable C solution to translate an address of a
	 * function to its name. On the cost of getting this routine simple
	 * and portable without ifdefs between the userland and the kernel
	 * just print the address of the function as-is.
	 *
	 * For better diagnostic messages in the userland, users shall use
	 * the full upstream version shipped along with the compiler toolchain.
	 */

	ASSERT(pData);

	if (isAlreadyReported(&pData->mLocation))
		return;

	DeserializeLocation(szLocation, LOCATION_MAXLEN, &pData->mLocation);

	Report(isFatal, "UBSan: Undefined Behavior in %s, call to function %#lx through pointer to incorrect function type %s\n",
	      szLocation, ulFunction, pData->mType->mTypeName);
}
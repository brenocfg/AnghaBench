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
struct CPointerOverflowData {int /*<<< orphan*/  mLocation; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct CPointerOverflowData*) ; 
 int /*<<< orphan*/  DeserializeLocation (char*,int,int /*<<< orphan*/ *) ; 
 int LOCATION_MAXLEN ; 
 int /*<<< orphan*/  Report (int,char*,char*,unsigned long,unsigned long) ; 
 scalar_t__ isAlreadyReported (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
HandlePointerOverflow(bool isFatal, struct CPointerOverflowData *pData, unsigned long ulBase, unsigned long ulResult)
{
	char szLocation[LOCATION_MAXLEN];

	ASSERT(pData);

	if (isAlreadyReported(&pData->mLocation))
		return;

	DeserializeLocation(szLocation, LOCATION_MAXLEN, &pData->mLocation);

	Report(isFatal, "UBSan: Undefined Behavior in %s, pointer expression with base %#lx overflowed to %#lx\n",
	       szLocation, ulBase, ulResult);
}
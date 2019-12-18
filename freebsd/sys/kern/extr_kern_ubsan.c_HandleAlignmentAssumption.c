#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * mFilename; } ;
struct CAlignmentAssumptionData {TYPE_1__ mAssumptionLocation; TYPE_1__ mLocation; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct CAlignmentAssumptionData*) ; 
 int /*<<< orphan*/  DeserializeLocation (char*,int,TYPE_1__*) ; 
 int LOCATION_MAXLEN ; 
 int /*<<< orphan*/  Report (int,char*,char*,unsigned long,unsigned long,unsigned long,...) ; 
 scalar_t__ isAlreadyReported (TYPE_1__*) ; 

__attribute__((used)) static void
HandleAlignmentAssumption(bool isFatal, struct CAlignmentAssumptionData *pData, unsigned long ulPointer, unsigned long ulAlignment, unsigned long ulOffset)
{
	char szLocation[LOCATION_MAXLEN];
	char szAssumptionLocation[LOCATION_MAXLEN];
	unsigned long ulRealPointer;

	ASSERT(pData);

	if (isAlreadyReported(&pData->mLocation))
		return;

	DeserializeLocation(szLocation, LOCATION_MAXLEN, &pData->mLocation);

	ulRealPointer = ulPointer - ulOffset;

	if (pData->mAssumptionLocation.mFilename != NULL) {
		DeserializeLocation(szAssumptionLocation, LOCATION_MAXLEN,
		    &pData->mAssumptionLocation);
		Report(isFatal, "UBSan: Undefined Behavior in %s, alignment assumption of %#lx for pointer %#lx (offset %#lx), asumption made in %s\n",
		    szLocation, ulAlignment, ulRealPointer, ulOffset,
		    szAssumptionLocation);
	} else {
		Report(isFatal, "UBSan: Undefined Behavior in %s, alignment assumption of %#lx for pointer %#lx (offset %#lx)\n",
		    szLocation, ulAlignment, ulRealPointer, ulOffset);
	}
}
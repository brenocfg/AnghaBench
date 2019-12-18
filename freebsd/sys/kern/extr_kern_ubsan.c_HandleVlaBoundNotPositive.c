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
struct CVLABoundData {int /*<<< orphan*/  mType; int /*<<< orphan*/  mLocation; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct CVLABoundData*) ; 
 int /*<<< orphan*/  DeserializeLocation (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeserializeNumber (char*,char*,int,int /*<<< orphan*/ ,unsigned long) ; 
 int LOCATION_MAXLEN ; 
 int NUMBER_MAXLEN ; 
 int /*<<< orphan*/  Report (int,char*,char*,char*) ; 
 scalar_t__ isAlreadyReported (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
HandleVlaBoundNotPositive(bool isFatal, struct CVLABoundData *pData, unsigned long ulBound)
{
	char szLocation[LOCATION_MAXLEN];
	char szBound[NUMBER_MAXLEN];

	ASSERT(pData);

	if (isAlreadyReported(&pData->mLocation))
		return;

	DeserializeLocation(szLocation, LOCATION_MAXLEN, &pData->mLocation);
	DeserializeNumber(szLocation, szBound, NUMBER_MAXLEN, pData->mType, ulBound);

	Report(isFatal, "UBSan: Undefined Behavior in %s, variable length array bound value %s <= 0\n",
	       szLocation, szBound);
}
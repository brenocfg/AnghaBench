#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct CShiftOutOfBoundsData {TYPE_1__* mLHSType; TYPE_1__* mRHSType; int /*<<< orphan*/  mLocation; } ;
struct TYPE_5__ {int /*<<< orphan*/  mTypeName; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct CShiftOutOfBoundsData*) ; 
 int /*<<< orphan*/  DeserializeLocation (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeserializeNumber (char*,char*,int,TYPE_1__*,unsigned long) ; 
 int LOCATION_MAXLEN ; 
 int NUMBER_MAXLEN ; 
 int /*<<< orphan*/  Report (int,char*,char*,char*,...) ; 
 scalar_t__ isAlreadyReported (int /*<<< orphan*/ *) ; 
 scalar_t__ isNegativeNumber (char*,TYPE_1__*,unsigned long) ; 
 scalar_t__ isShiftExponentTooLarge (char*,TYPE_1__*,unsigned long,char*) ; 
 char* zDeserializeTypeWidth (TYPE_1__*) ; 

__attribute__((used)) static void
HandleShiftOutOfBounds(bool isFatal, struct CShiftOutOfBoundsData *pData, unsigned long ulLHS, unsigned long ulRHS)
{
	char szLocation[LOCATION_MAXLEN];
	char szLHS[NUMBER_MAXLEN];
	char szRHS[NUMBER_MAXLEN];

	ASSERT(pData);

	if (isAlreadyReported(&pData->mLocation))
		return;

	DeserializeLocation(szLocation, LOCATION_MAXLEN, &pData->mLocation);
	DeserializeNumber(szLocation, szLHS, NUMBER_MAXLEN, pData->mLHSType, ulLHS);
	DeserializeNumber(szLocation, szRHS, NUMBER_MAXLEN, pData->mRHSType, ulRHS);

	if (isNegativeNumber(szLocation, pData->mRHSType, ulRHS))
		Report(isFatal, "UBSan: Undefined Behavior in %s, shift exponent %s is negative\n",
		       szLocation, szRHS);
	else if (isShiftExponentTooLarge(szLocation, pData->mRHSType, ulRHS, zDeserializeTypeWidth(pData->mLHSType)))
		Report(isFatal, "UBSan: Undefined Behavior in %s, shift exponent %s is too large for %zu-bit type %s\n",
		       szLocation, szRHS, zDeserializeTypeWidth(pData->mLHSType), pData->mLHSType->mTypeName);
	else if (isNegativeNumber(szLocation, pData->mLHSType, ulLHS))
		Report(isFatal, "UBSan: Undefined Behavior in %s, left shift of negative value %s\n",
		       szLocation, szLHS);
	else
		Report(isFatal, "UBSan: Undefined Behavior in %s, left shift of %s by %s places cannot be represented in type %s\n",
		       szLocation, szLHS, szRHS, pData->mLHSType->mTypeName);
}
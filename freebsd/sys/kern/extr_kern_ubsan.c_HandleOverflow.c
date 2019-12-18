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
struct COverflowData {TYPE_1__* mType; int /*<<< orphan*/  mLocation; } ;
struct TYPE_2__ {int /*<<< orphan*/  mTypeName; int /*<<< orphan*/  mTypeInfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct COverflowData*) ; 
 int /*<<< orphan*/  DeserializeLocation (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeserializeNumber (char*,char*,int,TYPE_1__*,unsigned long) ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LOCATION_MAXLEN ; 
 int NUMBER_MAXLEN ; 
 int /*<<< orphan*/  NUMBER_SIGNED_BIT ; 
 int /*<<< orphan*/  Report (int,char*,char*,char*,char*,char const*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ isAlreadyReported (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
HandleOverflow(bool isFatal, struct COverflowData *pData, unsigned long ulLHS, unsigned long ulRHS, const char *szOperation)
{
	char szLocation[LOCATION_MAXLEN];
	char szLHS[NUMBER_MAXLEN];
	char szRHS[NUMBER_MAXLEN];

	ASSERT(pData);

	if (isAlreadyReported(&pData->mLocation))
		return;

	DeserializeLocation(szLocation, LOCATION_MAXLEN, &pData->mLocation);
	DeserializeNumber(szLocation, szLHS, NUMBER_MAXLEN, pData->mType, ulLHS);
	DeserializeNumber(szLocation, szRHS, NUMBER_MAXLEN, pData->mType, ulRHS);

	Report(isFatal, "UBSan: Undefined Behavior in %s, %s integer overflow: %s %s %s cannot be represented in type %s\n",
	       szLocation, ISSET(pData->mType->mTypeInfo, NUMBER_SIGNED_BIT) ? "signed" : "unsigned", szLHS, szOperation, szRHS, pData->mType->mTypeName);
}
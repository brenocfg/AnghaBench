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
struct CInvalidValueData {TYPE_1__* mType; int /*<<< orphan*/  mLocation; } ;
struct TYPE_2__ {int /*<<< orphan*/  mTypeName; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct CInvalidValueData*) ; 
 int /*<<< orphan*/  DeserializeLocation (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeserializeNumber (char*,char*,int,TYPE_1__*,unsigned long) ; 
 int LOCATION_MAXLEN ; 
 int NUMBER_MAXLEN ; 
 int /*<<< orphan*/  Report (int,char*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ isAlreadyReported (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
HandleLoadInvalidValue(bool isFatal, struct CInvalidValueData *pData, unsigned long ulValue)
{
	char szLocation[LOCATION_MAXLEN];
	char szValue[NUMBER_MAXLEN];

	ASSERT(pData);

	if (isAlreadyReported(&pData->mLocation))
		return;

	DeserializeLocation(szLocation, LOCATION_MAXLEN, &pData->mLocation);
	DeserializeNumber(szLocation, szValue, NUMBER_MAXLEN, pData->mType, ulValue);

	Report(isFatal, "UBSan: Undefined Behavior in %s, load of value %s is not a valid value for type %s\n",
	       szLocation, szValue, pData->mType->mTypeName);
}
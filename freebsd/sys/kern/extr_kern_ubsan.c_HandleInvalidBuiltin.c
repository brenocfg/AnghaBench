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
struct CInvalidBuiltinData {int /*<<< orphan*/  mKind; int /*<<< orphan*/  mLocation; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct CInvalidBuiltinData*) ; 
 int /*<<< orphan*/  DeserializeBuiltinCheckKind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeserializeLocation (char*,int,int /*<<< orphan*/ *) ; 
 int LOCATION_MAXLEN ; 
 int /*<<< orphan*/  Report (int,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ isAlreadyReported (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
HandleInvalidBuiltin(bool isFatal, struct CInvalidBuiltinData *pData)
{
	char szLocation[LOCATION_MAXLEN];

	ASSERT(pData);

	if (isAlreadyReported(&pData->mLocation))
		return;

	DeserializeLocation(szLocation, LOCATION_MAXLEN, &pData->mLocation);

	Report(isFatal, "UBSan: Undefined Behavior in %s, passing zero to %s, which is not a valid argument\n",
	       szLocation, DeserializeBuiltinCheckKind(pData->mKind));
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt32 ;
struct TYPE_4__ {size_t Size; int /*<<< orphan*/  Data; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ CSzData ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int CountDefinedBits (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SKIP_DATA (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  SZ_ERROR_ARCHIVE ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  SZ_READ_BYTE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static SRes SkipBitUi32s(CSzData *sd, UInt32 numItems)
{
  Byte allAreDefined;
  UInt32 numDefined = numItems;
  SZ_READ_BYTE(allAreDefined);
  if (!allAreDefined)
  {
    size_t numBytes = (numItems + 7) >> 3;
    if (numBytes > sd->Size)
      return SZ_ERROR_ARCHIVE;
    numDefined = CountDefinedBits(sd->Data, numItems);
    SKIP_DATA(sd, numBytes);
  }
  if (numDefined > (sd->Size >> 2))
    return SZ_ERROR_ARCHIVE;
  SKIP_DATA(sd, (size_t)numDefined * 4);
  return SZ_OK;
}
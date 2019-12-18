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
struct TYPE_4__ {int Size; int /*<<< orphan*/ * Data; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ CSzData ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  SKIP_DATA (TYPE_1__*,int) ; 
 int /*<<< orphan*/  SZ_ERROR_ARCHIVE ; 
 int /*<<< orphan*/  SZ_OK ; 

__attribute__((used)) static SRes RememberBitVector(CSzData *sd, UInt32 numItems, const Byte **v)
{
  UInt32 numBytes = (numItems + 7) >> 3;
  if (numBytes > sd->Size)
    return SZ_ERROR_ARCHIVE;
  *v = sd->Data;
  SKIP_DATA(sd, numBytes);
  return SZ_OK;
}
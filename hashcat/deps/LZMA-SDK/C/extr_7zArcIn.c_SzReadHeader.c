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
struct TYPE_4__ {scalar_t__ Size; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  int /*<<< orphan*/  ILookInStream ;
typedef  TYPE_1__ CSzData ;
typedef  int /*<<< orphan*/  CSzArEx ;
typedef  int /*<<< orphan*/  CBuf ;

/* Variables and functions */
 int /*<<< orphan*/  Buf_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Buf_Init (int /*<<< orphan*/ *) ; 
 int NUM_ADDITIONAL_STREAMS_MAX ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_ERROR_FAIL ; 
 int /*<<< orphan*/  SzReadHeader2 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static SRes SzReadHeader(
    CSzArEx *p,
    CSzData *sd,
    ILookInStream *inStream,
    ISzAllocPtr allocMain,
    ISzAllocPtr allocTemp)
{
  UInt32 i;
  UInt32 numTempBufs = 0;
  SRes res;
  CBuf tempBufs[NUM_ADDITIONAL_STREAMS_MAX];

  for (i = 0; i < NUM_ADDITIONAL_STREAMS_MAX; i++)
    Buf_Init(tempBufs + i);
  
  res = SzReadHeader2(p, sd, inStream,
      tempBufs, &numTempBufs,
      allocMain, allocTemp);
  
  for (i = 0; i < NUM_ADDITIONAL_STREAMS_MAX; i++)
    Buf_Free(tempBufs + i, allocTemp);

  RINOK(res);

  if (sd->Size != 0)
    return SZ_ERROR_FAIL;

  return res;
}
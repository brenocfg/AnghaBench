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
typedef  int /*<<< orphan*/  UInt32 ;
struct TYPE_5__ {int /*<<< orphan*/  Defs; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  int /*<<< orphan*/  CSzData ;
typedef  TYPE_1__ CSzBitUi32s ;

/* Variables and functions */
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadBitVector (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadUi32s (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SzBitUi32s_Free (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static SRes ReadBitUi32s(CSzData *sd, UInt32 numItems, CSzBitUi32s *crcs, ISzAllocPtr alloc)
{
  SzBitUi32s_Free(crcs, alloc);
  RINOK(ReadBitVector(sd, numItems, &crcs->Defs, alloc));
  return ReadUi32s(sd, numItems, crcs, alloc);
}
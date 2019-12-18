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
typedef  scalar_t__ UInt32 ;
struct TYPE_4__ {scalar_t__ keepSizeBefore; scalar_t__ keepSizeAfter; scalar_t__ blockSize; int /*<<< orphan*/ * bufferBase; scalar_t__ directInput; } ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  TYPE_1__ CMatchFinder ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 scalar_t__ ISzAlloc_Alloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  LzInWindow_Free (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int LzInWindow_Create(CMatchFinder *p, UInt32 keepSizeReserv, ISzAllocPtr alloc)
{
  UInt32 blockSize = p->keepSizeBefore + p->keepSizeAfter + keepSizeReserv;
  if (p->directInput)
  {
    p->blockSize = blockSize;
    return 1;
  }
  if (!p->bufferBase || p->blockSize != blockSize)
  {
    LzInWindow_Free(p, alloc);
    p->blockSize = blockSize;
    p->bufferBase = (Byte *)ISzAlloc_Alloc(alloc, (size_t)blockSize);
  }
  return (p->bufferBase != NULL);
}
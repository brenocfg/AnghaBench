#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t allocated; int /*<<< orphan*/ * blocks; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  TYPE_1__ CXzEncIndex ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 scalar_t__ ISzAlloc_Alloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SZ_ERROR_MEM ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static SRes XzEncIndex_ReAlloc(CXzEncIndex *p, size_t newSize, ISzAllocPtr alloc)
{
  Byte *blocks = (Byte *)ISzAlloc_Alloc(alloc, newSize);
  if (!blocks)
    return SZ_ERROR_MEM;
  if (p->size != 0)
    memcpy(blocks, p->blocks, p->size);
  if (p->blocks)
    ISzAlloc_Free(alloc, p->blocks);
  p->blocks = blocks;
  p->allocated = newSize;
  return SZ_OK;
}
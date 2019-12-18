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
typedef  unsigned int UInt64 ;
struct TYPE_4__ {unsigned int allocated; unsigned int size; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  TYPE_1__ CXzEncIndex ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  SZ_ERROR_MEM ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  XzEncIndex_ReAlloc (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 unsigned int Xz_WriteVarInt (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static SRes XzEncIndex_PreAlloc(CXzEncIndex *p, UInt64 numBlocks, UInt64 unpackSize, UInt64 totalSize, ISzAllocPtr alloc)
{
  UInt64 pos;
  {
    Byte buf[32];
    unsigned pos2 = Xz_WriteVarInt(buf, totalSize);
    pos2 += Xz_WriteVarInt(buf + pos2, unpackSize);
    pos = numBlocks * pos2;
  }
  
  if (pos <= p->allocated - p->size)
    return SZ_OK;
  {
    UInt64 newSize64 = p->size + pos;
    size_t newSize = (size_t)newSize64;
    if (newSize != newSize64)
      return SZ_ERROR_MEM;
    return XzEncIndex_ReAlloc(p, newSize, alloc);
  }
}
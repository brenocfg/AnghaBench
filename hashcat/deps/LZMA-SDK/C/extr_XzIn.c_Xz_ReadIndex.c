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
typedef  int UInt64 ;
typedef  int UInt32 ;
typedef  scalar_t__ SRes ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  int /*<<< orphan*/  ILookInStream ;
typedef  int /*<<< orphan*/  CXzStream ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 scalar_t__ ISzAlloc_Alloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ LookInStream_Read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,scalar_t__) ; 
 scalar_t__ SZ_ERROR_MEM ; 
 scalar_t__ SZ_ERROR_UNSUPPORTED ; 
 scalar_t__ SZ_OK ; 
 scalar_t__ Xz_ReadIndex2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static SRes Xz_ReadIndex(CXzStream *p, ILookInStream *stream, UInt64 indexSize, ISzAllocPtr alloc)
{
  SRes res;
  size_t size;
  Byte *buf;
  if (indexSize > ((UInt32)1 << 31))
    return SZ_ERROR_UNSUPPORTED;
  size = (size_t)indexSize;
  if (size != indexSize)
    return SZ_ERROR_UNSUPPORTED;
  buf = (Byte *)ISzAlloc_Alloc(alloc, size);
  if (!buf)
    return SZ_ERROR_MEM;
  res = LookInStream_Read2(stream, buf, size, SZ_ERROR_UNSUPPORTED);
  if (res == SZ_OK)
    res = Xz_ReadIndex2(p, buf, size, alloc);
  ISzAlloc_Free(alloc, buf);
  return res;
}
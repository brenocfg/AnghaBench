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
typedef  int /*<<< orphan*/  UInt32 ;
typedef  scalar_t__ SizeT ;
typedef  scalar_t__ SRes ;
typedef  int /*<<< orphan*/  ELzmaStatus ;
typedef  int Byte ;

/* Variables and functions */
 scalar_t__ LZMA86_HEADER_SIZE ; 
 int /*<<< orphan*/  LZMA_FINISH_ANY ; 
 int /*<<< orphan*/  LZMA_PROPS_SIZE ; 
 scalar_t__ LzmaDecode (int*,scalar_t__*,int const*,scalar_t__*,int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SZ_ERROR_INPUT_EOF ; 
 scalar_t__ SZ_ERROR_UNSUPPORTED ; 
 scalar_t__ SZ_OK ; 
 int /*<<< orphan*/  g_Alloc ; 
 int /*<<< orphan*/  x86_Convert (int*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x86_Convert_Init (int /*<<< orphan*/ ) ; 

SRes Lzma86_Decode(Byte *dest, SizeT *destLen, const Byte *src, SizeT *srcLen)
{
  SRes res;
  int useFilter;
  SizeT inSizePure;
  ELzmaStatus status;

  if (*srcLen < LZMA86_HEADER_SIZE)
    return SZ_ERROR_INPUT_EOF;

  useFilter = src[0];

  if (useFilter > 1)
  {
    *destLen = 0;
    return SZ_ERROR_UNSUPPORTED;
  }

  inSizePure = *srcLen - LZMA86_HEADER_SIZE;
  res = LzmaDecode(dest, destLen, src + LZMA86_HEADER_SIZE, &inSizePure,
      src + 1, LZMA_PROPS_SIZE, LZMA_FINISH_ANY, &status, &g_Alloc);
  *srcLen = inSizePure + LZMA86_HEADER_SIZE;
  if (res != SZ_OK)
    return res;
  if (useFilter == 1)
  {
    UInt32 x86State;
    x86_Convert_Init(x86State);
    x86_Convert(dest, *destLen, 0, &x86State, 0);
  }
  return SZ_OK;
}
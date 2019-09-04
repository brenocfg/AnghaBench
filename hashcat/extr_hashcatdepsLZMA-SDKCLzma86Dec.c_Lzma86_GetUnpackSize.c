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
typedef  scalar_t__ SizeT ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 scalar_t__ LZMA86_HEADER_SIZE ; 
 unsigned int LZMA86_SIZE_OFFSET ; 
 int /*<<< orphan*/  SZ_ERROR_INPUT_EOF ; 
 int /*<<< orphan*/  SZ_OK ; 

SRes Lzma86_GetUnpackSize(const Byte *src, SizeT srcLen, UInt64 *unpackSize)
{
  unsigned i;
  if (srcLen < LZMA86_HEADER_SIZE)
    return SZ_ERROR_INPUT_EOF;
  *unpackSize = 0;
  for (i = 0; i < sizeof(UInt64); i++)
    *unpackSize += ((UInt64)src[LZMA86_SIZE_OFFSET + i]) << (8 * i);
  return SZ_OK;
}
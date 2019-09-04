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
typedef  scalar_t__ UInt32 ;
typedef  int /*<<< orphan*/  SRes ;
typedef  scalar_t__ Byte ;

/* Variables and functions */
 int /*<<< orphan*/  SZ_ERROR_ARCHIVE ; 
 int /*<<< orphan*/  SZ_OK ; 

__attribute__((used)) static SRes SzReadFileNames(const Byte *data, size_t size, UInt32 numFiles, size_t *offsets)
{
  size_t pos = 0;
  *offsets++ = 0;
  if (numFiles == 0)
    return (size == 0) ? SZ_OK : SZ_ERROR_ARCHIVE;
  if (size < 2)
    return SZ_ERROR_ARCHIVE;
  if (data[size - 2] != 0 || data[size - 1] != 0)
    return SZ_ERROR_ARCHIVE;
  do
  {
    const Byte *p;
    if (pos == size)
      return SZ_ERROR_ARCHIVE;
    for (p = data + pos;
      #ifdef _WIN32
      *(const UInt16 *)p != 0
      #else
      p[0] != 0 || p[1] != 0
      #endif
      ; p += 2);
    pos = p - data + 2;
    *offsets++ = (pos >> 1);
  }
  while (--numFiles);
  return (pos == size) ? SZ_OK : SZ_ERROR_ARCHIVE;
}
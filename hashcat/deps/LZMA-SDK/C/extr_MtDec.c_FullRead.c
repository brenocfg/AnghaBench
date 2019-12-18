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
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISeqInStream ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  ISeqInStream_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_OK ; 

__attribute__((used)) static SRes FullRead(ISeqInStream *stream, Byte *data, size_t *processedSize)
{
  size_t size = *processedSize;
  *processedSize = 0;
  while (size != 0)
  {
    size_t cur = size;
    SRes res = ISeqInStream_Read(stream, data, &cur);
    *processedSize += cur;
    data += cur;
    size -= cur;
    RINOK(res);
    if (cur == 0)
      return SZ_OK;
  }
  return SZ_OK;
}
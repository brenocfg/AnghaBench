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
typedef  int /*<<< orphan*/  ILookInStream ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  ILookInStream_Read (int /*<<< orphan*/  const*,void*,size_t*) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_OK ; 

SRes LookInStream_Read2(const ILookInStream *stream, void *buf, size_t size, SRes errorType)
{
  while (size != 0)
  {
    size_t processed = size;
    RINOK(ILookInStream_Read(stream, buf, &processed));
    if (processed == 0)
      return errorType;
    buf = (void *)((Byte *)buf + processed);
    size -= processed;
  }
  return SZ_OK;
}
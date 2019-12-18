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
typedef  scalar_t__ UInt32 ;
struct TYPE_3__ {int streamEndWasReached; scalar_t__ result; scalar_t__ streamPos; scalar_t__ pos; scalar_t__ directInputRem; int blockSize; scalar_t__ keepSizeAfter; int /*<<< orphan*/  stream; int /*<<< orphan*/ * bufferBase; int /*<<< orphan*/ * buffer; scalar_t__ directInput; } ;
typedef  TYPE_1__ CMatchFinder ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 scalar_t__ ISeqInStream_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ SZ_OK ; 

__attribute__((used)) static void MatchFinder_ReadBlock(CMatchFinder *p)
{
  if (p->streamEndWasReached || p->result != SZ_OK)
    return;

  /* We use (p->streamPos - p->pos) value. (p->streamPos < p->pos) is allowed. */

  if (p->directInput)
  {
    UInt32 curSize = 0xFFFFFFFF - (p->streamPos - p->pos);
    if (curSize > p->directInputRem)
      curSize = (UInt32)p->directInputRem;
    p->directInputRem -= curSize;
    p->streamPos += curSize;
    if (p->directInputRem == 0)
      p->streamEndWasReached = 1;
    return;
  }
  
  for (;;)
  {
    Byte *dest = p->buffer + (p->streamPos - p->pos);
    size_t size = (p->bufferBase + p->blockSize - dest);
    if (size == 0)
      return;

    p->result = ISeqInStream_Read(p->stream, dest, &size);
    if (p->result != SZ_OK)
      return;
    if (size == 0)
    {
      p->streamEndWasReached = 1;
      return;
    }
    p->streamPos += (UInt32)size;
    if (p->streamPos - p->pos > p->keepSizeAfter)
      return;
  }
}
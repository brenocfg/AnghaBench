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
struct TYPE_3__ {scalar_t__ outDataWritten; void* decodeToStreamSignature; void* parseMode; scalar_t__ decodeOnlyOneBlock; scalar_t__ padSize; scalar_t__ numTotalBlocks; scalar_t__ numFinishedStreams; scalar_t__ numStartedStreams; scalar_t__ pos; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ CXzUnpacker ;

/* Variables and functions */
 void* False ; 
 int /*<<< orphan*/  XZ_STATE_STREAM_HEADER ; 

void XzUnpacker_Init(CXzUnpacker *p)
{
  p->state = XZ_STATE_STREAM_HEADER;
  p->pos = 0;
  p->numStartedStreams = 0;
  p->numFinishedStreams = 0;
  p->numTotalBlocks = 0;
  p->padSize = 0;
  p->decodeOnlyOneBlock = 0;

  p->parseMode = False;
  p->decodeToStreamSignature = False;

  // p->outBuf = NULL;
  // p->outBufSize = 0;
  p->outDataWritten = 0;
}
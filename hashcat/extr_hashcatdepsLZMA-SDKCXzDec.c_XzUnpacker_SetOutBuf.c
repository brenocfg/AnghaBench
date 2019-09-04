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
struct TYPE_3__ {size_t outBufSize; int /*<<< orphan*/ * outBuf; } ;
typedef  TYPE_1__ CXzUnpacker ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */

void XzUnpacker_SetOutBuf(CXzUnpacker *p, Byte *outBuf, size_t outBufSize)
{
  p->outBuf = outBuf;
  p->outBufSize = outBufSize;
}
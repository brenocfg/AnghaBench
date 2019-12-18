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
struct TYPE_4__ {scalar_t__ outBufSize; int /*<<< orphan*/ * outBuf; int /*<<< orphan*/  decoder; } ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  TYPE_1__ CXzUnpacker ;

/* Variables and functions */
 int /*<<< orphan*/  MixCoder_Construct (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XzUnpacker_Init (TYPE_1__*) ; 

void XzUnpacker_Construct(CXzUnpacker *p, ISzAllocPtr alloc)
{
  MixCoder_Construct(&p->decoder, alloc);
  p->outBuf = NULL;
  p->outBufSize = 0;
  XzUnpacker_Init(p);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* coders; int /*<<< orphan*/ * outBuf; scalar_t__ outBufSize; scalar_t__ numCoders; int /*<<< orphan*/ * buf; int /*<<< orphan*/  alloc; } ;
struct TYPE_4__ {int /*<<< orphan*/ * p; } ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  TYPE_2__ CMixCoder ;

/* Variables and functions */
 unsigned int MIXCODER_NUM_FILTERS_MAX ; 

__attribute__((used)) static void MixCoder_Construct(CMixCoder *p, ISzAllocPtr alloc)
{
  unsigned i;
  p->alloc = alloc;
  p->buf = NULL;
  p->numCoders = 0;
  
  p->outBufSize = 0;
  p->outBuf = NULL;
  // p->SingleBufMode = False;

  for (i = 0; i < MIXCODER_NUM_FILTERS_MAX; i++)
    p->coders[i].p = NULL;
}
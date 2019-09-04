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
struct TYPE_3__ {int inBufSize_ST; int outStep_ST; int numThreads; int inBufSize_MT; int outBlockMax; int inBlockMax; } ;
typedef  TYPE_1__ CLzma2DecMtProps ;

/* Variables and functions */
 int LZMA2DECMT_OUT_BLOCK_MAX_DEFAULT ; 

void Lzma2DecMtProps_Init(CLzma2DecMtProps *p)
{
  p->inBufSize_ST = 1 << 20;
  p->outStep_ST = 1 << 20;

  #ifndef _7ZIP_ST
  p->numThreads = 1;
  p->inBufSize_MT = 1 << 18;
  p->outBlockMax = LZMA2DECMT_OUT_BLOCK_MAX_DEFAULT;
  p->inBlockMax = p->outBlockMax + p->outBlockMax / 16;
  #endif
}
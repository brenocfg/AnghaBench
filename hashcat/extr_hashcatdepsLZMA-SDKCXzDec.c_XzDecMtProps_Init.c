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
struct TYPE_3__ {int inBufSize_ST; int outStep_ST; int numThreads; int inBufSize_MT; int memUseMax; int /*<<< orphan*/  ignoreErrors; } ;
typedef  TYPE_1__ CXzDecMtProps ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 

void XzDecMtProps_Init(CXzDecMtProps *p)
{
  p->inBufSize_ST = 1 << 18;
  p->outStep_ST = 1 << 20;
  p->ignoreErrors = False;

  #ifndef _7ZIP_ST
  p->numThreads = 1;
  p->inBufSize_MT = 1 << 18;
  p->memUseMax = sizeof(size_t) << 28;
  #endif
}
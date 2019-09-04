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
struct TYPE_3__ {scalar_t__ totalOutSize; scalar_t__ totalInSize; int /*<<< orphan*/  res; int /*<<< orphan*/ * progress; } ;
typedef  int /*<<< orphan*/  ICompressProgress ;
typedef  TYPE_1__ CMtProgress ;

/* Variables and functions */
 int /*<<< orphan*/  SZ_OK ; 

void MtProgress_Init(CMtProgress *p, ICompressProgress *progress)
{
  p->progress = progress;
  p->res = SZ_OK;
  p->totalInSize = 0;
  p->totalOutSize = 0;
}
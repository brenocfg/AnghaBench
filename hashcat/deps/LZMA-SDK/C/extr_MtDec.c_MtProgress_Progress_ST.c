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
struct TYPE_3__ {scalar_t__ res; int /*<<< orphan*/  totalOutSize; int /*<<< orphan*/  totalInSize; scalar_t__ progress; } ;
typedef  scalar_t__ SRes ;
typedef  TYPE_1__ CMtProgress ;

/* Variables and functions */
 scalar_t__ ICompressProgress_Progress (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SZ_ERROR_PROGRESS ; 
 scalar_t__ SZ_OK ; 

SRes MtProgress_Progress_ST(CMtProgress *p)
{
  if (p->res == SZ_OK && p->progress)
    if (ICompressProgress_Progress(p->progress, p->totalInSize, p->totalOutSize) != SZ_OK)
      p->res = SZ_ERROR_PROGRESS;
  return p->res;
}
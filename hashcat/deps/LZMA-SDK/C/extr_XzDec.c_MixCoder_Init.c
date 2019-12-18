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
struct TYPE_5__ {unsigned int numCoders; int /*<<< orphan*/  status; void* res; int /*<<< orphan*/  wasFinished; scalar_t__ outWritten; void** results; TYPE_1__* coders; scalar_t__* finished; scalar_t__* pos; scalar_t__* size; } ;
struct TYPE_4__ {int /*<<< orphan*/  p; int /*<<< orphan*/  (* Init ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ IStateCoder ;
typedef  TYPE_2__ CMixCoder ;

/* Variables and functions */
 int /*<<< orphan*/  CODER_STATUS_NOT_SPECIFIED ; 
 int /*<<< orphan*/  False ; 
 int MIXCODER_NUM_FILTERS_MAX ; 
 void* SZ_OK ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void MixCoder_Init(CMixCoder *p)
{
  unsigned i;
  for (i = 0; i < MIXCODER_NUM_FILTERS_MAX - 1; i++)
  {
    p->size[i] = 0;
    p->pos[i] = 0;
    p->finished[i] = 0;
  }
  for (i = 0; i < p->numCoders; i++)
  {
    IStateCoder *coder = &p->coders[i];
    coder->Init(coder->p);
    p->results[i] = SZ_OK;
  }
  p->outWritten = 0;
  p->wasFinished = False;
  p->res = SZ_OK;
  p->status = CODER_STATUS_NOT_SPECIFIED;
}
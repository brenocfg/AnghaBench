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
struct TYPE_5__ {int /*<<< orphan*/ * buf; int /*<<< orphan*/  alloc; TYPE_1__* coders; scalar_t__ numCoders; } ;
struct TYPE_4__ {int /*<<< orphan*/ * p; int /*<<< orphan*/  (* Free ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ IStateCoder ;
typedef  TYPE_2__ CMixCoder ;

/* Variables and functions */
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int MIXCODER_NUM_FILTERS_MAX ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void MixCoder_Free(CMixCoder *p)
{
  unsigned i;
  p->numCoders = 0;
  for (i = 0; i < MIXCODER_NUM_FILTERS_MAX; i++)
  {
    IStateCoder *sc = &p->coders[i];
    if (sc->p)
    {
      sc->Free(sc->p, p->alloc);
      sc->p = NULL;
    }
  }
  if (p->buf)
  {
    ISzAlloc_Free(p->alloc, p->buf);
    p->buf = NULL; /* 9.31: the BUG was fixed */
  }
}
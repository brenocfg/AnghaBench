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
struct TYPE_3__ {int /*<<< orphan*/ * lzma2; int /*<<< orphan*/  filter; int /*<<< orphan*/  sb; } ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  TYPE_1__ CLzma2WithFilters ;

/* Variables and functions */
 int /*<<< orphan*/  Lzma2Enc_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SbEncInStream_Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SeqInFilter_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Lzma2WithFilters_Free(CLzma2WithFilters *p, ISzAllocPtr alloc)
{
  #ifdef USE_SUBBLOCK
  SbEncInStream_Free(&p->sb);
  #endif

  SeqInFilter_Free(&p->filter, alloc);
  if (p->lzma2)
  {
    Lzma2Enc_Destroy(p->lzma2);
    p->lzma2 = NULL;
  }
}
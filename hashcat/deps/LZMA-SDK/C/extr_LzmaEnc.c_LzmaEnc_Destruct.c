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
struct TYPE_4__ {int /*<<< orphan*/  rc; int /*<<< orphan*/  matchFinderBase; int /*<<< orphan*/  matchFinderMt; } ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  TYPE_1__ CLzmaEnc ;

/* Variables and functions */
 int /*<<< orphan*/  LzmaEnc_FreeLits (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MatchFinderMt_Destruct (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MatchFinder_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RangeEnc_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void LzmaEnc_Destruct(CLzmaEnc *p, ISzAllocPtr alloc, ISzAllocPtr allocBig)
{
  #ifndef _7ZIP_ST
  MatchFinderMt_Destruct(&p->matchFinderMt, allocBig);
  #endif
  
  MatchFinder_Free(&p->matchFinderBase, allocBig);
  LzmaEnc_FreeLits(p, alloc);
  RangeEnc_Free(&p->rc, alloc);
}
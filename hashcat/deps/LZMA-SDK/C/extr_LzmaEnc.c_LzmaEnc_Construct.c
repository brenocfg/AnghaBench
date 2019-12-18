#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * MatchFinder; } ;
struct TYPE_6__ {int /*<<< orphan*/ * litProbs; } ;
struct TYPE_7__ {TYPE_1__ saveState; int /*<<< orphan*/ * litProbs; int /*<<< orphan*/  ProbPrices; int /*<<< orphan*/  g_FastPos; int /*<<< orphan*/  matchFinderBase; TYPE_3__ matchFinderMt; int /*<<< orphan*/  rc; } ;
typedef  int /*<<< orphan*/  CLzmaEncProps ;
typedef  TYPE_2__ CLzmaEnc ;

/* Variables and functions */
 int /*<<< orphan*/  LzmaEncProps_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LzmaEnc_FastPosInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LzmaEnc_InitPriceTables (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LzmaEnc_SetProps (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MatchFinderMt_Construct (TYPE_3__*) ; 
 int /*<<< orphan*/  MatchFinder_Construct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RangeEnc_Construct (int /*<<< orphan*/ *) ; 

void LzmaEnc_Construct(CLzmaEnc *p)
{
  RangeEnc_Construct(&p->rc);
  MatchFinder_Construct(&p->matchFinderBase);
  
  #ifndef _7ZIP_ST
  MatchFinderMt_Construct(&p->matchFinderMt);
  p->matchFinderMt.MatchFinder = &p->matchFinderBase;
  #endif

  {
    CLzmaEncProps props;
    LzmaEncProps_Init(&props);
    LzmaEnc_SetProps(p, &props);
  }

  #ifndef LZMA_LOG_BSR
  LzmaEnc_FastPosInit(p->g_FastPos);
  #endif

  LzmaEnc_InitPriceTables(p->ProbPrices);
  p->litProbs = NULL;
  p->saveState.litProbs = NULL;

}
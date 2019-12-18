#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ tableSize; } ;
struct TYPE_6__ {int pb; int /*<<< orphan*/  ProbPrices; int /*<<< orphan*/  repLenProbs; TYPE_3__ repLenEnc; int /*<<< orphan*/  lenProbs; TYPE_3__ lenEnc; int /*<<< orphan*/  repLenEncCounter; scalar_t__ numFastBytes; int /*<<< orphan*/  fastMode; } ;
typedef  TYPE_1__ CLzmaEnc ;

/* Variables and functions */
 int /*<<< orphan*/  FillAlignPrices (TYPE_1__*) ; 
 int /*<<< orphan*/  FillDistancesPrices (TYPE_1__*) ; 
 scalar_t__ LZMA_MATCH_LEN_MIN ; 
 int /*<<< orphan*/  LenPriceEnc_UpdateTables (TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REP_LEN_COUNT ; 

void LzmaEnc_InitPrices(CLzmaEnc *p)
{
  if (!p->fastMode)
  {
    FillDistancesPrices(p);
    FillAlignPrices(p);
  }

  p->lenEnc.tableSize =
  p->repLenEnc.tableSize =
      p->numFastBytes + 1 - LZMA_MATCH_LEN_MIN;

  p->repLenEncCounter = REP_LEN_COUNT;

  LenPriceEnc_UpdateTables(&p->lenEnc, 1 << p->pb, &p->lenProbs, p->ProbPrices);
  LenPriceEnc_UpdateTables(&p->repLenEnc, 1 << p->pb, &p->repLenProbs, p->ProbPrices);
}
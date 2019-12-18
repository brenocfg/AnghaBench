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
typedef  int UInt32 ;
struct TYPE_4__ {int range; } ;
typedef  TYPE_1__ CRangeEnc ;
typedef  int /*<<< orphan*/  CLzmaProb ;

/* Variables and functions */
 int /*<<< orphan*/  RC_BIT (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void LitEnc_Encode(CRangeEnc *p, CLzmaProb *probs, UInt32 sym)
{
  UInt32 range = p->range;
  sym |= 0x100;
  do
  {
    UInt32 ttt, newBound;
    // RangeEnc_EncodeBit(p, probs + (sym >> 8), (sym >> 7) & 1);
    CLzmaProb *prob = probs + (sym >> 8);
    UInt32 bit = (sym >> 7) & 1;
    sym <<= 1;
    RC_BIT(p, prob, bit);
  }
  while (sym < 0x10000);
  p->range = range;
}
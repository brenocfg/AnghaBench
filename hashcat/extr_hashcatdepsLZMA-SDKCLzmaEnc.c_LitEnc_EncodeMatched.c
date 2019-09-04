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

__attribute__((used)) static void LitEnc_EncodeMatched(CRangeEnc *p, CLzmaProb *probs, UInt32 symbol, UInt32 matchByte)
{
  UInt32 range = p->range;
  UInt32 offs = 0x100;
  symbol |= 0x100;
  do
  {
    UInt32 ttt, newBound;
    CLzmaProb *prob;
    UInt32 bit;
    matchByte <<= 1;
    // RangeEnc_EncodeBit(p, probs + (offs + (matchByte & offs) + (symbol >> 8)), (symbol >> 7) & 1);
    prob = probs + (offs + (matchByte & offs) + (symbol >> 8));
    bit = (symbol >> 7) & 1;
    symbol <<= 1;
    offs &= ~(matchByte ^ symbol);
    RC_BIT(p, prob, bit);
  }
  while (symbol < 0x10000);
  p->range = range;
}
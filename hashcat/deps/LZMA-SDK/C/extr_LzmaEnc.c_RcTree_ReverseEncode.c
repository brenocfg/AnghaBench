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
typedef  int /*<<< orphan*/  UInt32 ;
struct TYPE_4__ {int /*<<< orphan*/  range; } ;
typedef  TYPE_1__ CRangeEnc ;
typedef  int /*<<< orphan*/  CLzmaProb ;

/* Variables and functions */
 int /*<<< orphan*/  RC_BIT (TYPE_1__*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void RcTree_ReverseEncode(CRangeEnc *rc, CLzmaProb *probs, unsigned numBits, unsigned sym)
{
  UInt32 range = rc->range;
  unsigned m = 1;
  do
  {
    UInt32 ttt, newBound;
    unsigned bit = sym & 1;
    // RangeEnc_EncodeBit(rc, probs + m, bit);
    sym >>= 1;
    RC_BIT(rc, probs + m, bit);
    m = (m << 1) | bit;
  }
  while (--numBits);
  rc->range = range;
}
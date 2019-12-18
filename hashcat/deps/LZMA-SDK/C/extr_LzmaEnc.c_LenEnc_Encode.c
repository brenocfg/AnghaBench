#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void* UInt32 ;
struct TYPE_11__ {int /*<<< orphan*/  high; int /*<<< orphan*/ * low; } ;
struct TYPE_10__ {void* range; } ;
typedef  TYPE_1__ CRangeEnc ;
typedef  int /*<<< orphan*/  CLzmaProb ;
typedef  TYPE_2__ CLenEnc ;

/* Variables and functions */
 int /*<<< orphan*/  LitEnc_Encode (TYPE_1__*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  RC_BIT (TYPE_1__*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  RC_BIT_0 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RC_BIT_1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RC_BIT_PRE (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int kLenNumLowBits ; 
 unsigned int kLenNumLowSymbols ; 

__attribute__((used)) static void LenEnc_Encode(CLenEnc *p, CRangeEnc *rc, unsigned sym, unsigned posState)
{
  UInt32 range, ttt, newBound;
  CLzmaProb *probs = p->low;
  range = rc->range;
  RC_BIT_PRE(rc, probs);
  if (sym >= kLenNumLowSymbols)
  {
    RC_BIT_1(rc, probs);
    probs += kLenNumLowSymbols;
    RC_BIT_PRE(rc, probs);
    if (sym >= kLenNumLowSymbols * 2)
    {
      RC_BIT_1(rc, probs);
      rc->range = range;
      // RcTree_Encode(rc, p->high, kLenNumHighBits, sym - kLenNumLowSymbols * 2);
      LitEnc_Encode(rc, p->high, sym - kLenNumLowSymbols * 2);
      return;
    }
    sym -= kLenNumLowSymbols;
  }

  // RcTree_Encode(rc, probs + (posState << kLenNumLowBits), kLenNumLowBits, sym);
  {
    unsigned m;
    unsigned bit;
    RC_BIT_0(rc, probs);
    probs += (posState << (1 + kLenNumLowBits));
    bit = (sym >> 2)    ; RC_BIT(rc, probs + 1, bit); m = (1 << 1) + bit;
    bit = (sym >> 1) & 1; RC_BIT(rc, probs + m, bit); m = (m << 1) + bit;
    bit =  sym       & 1; RC_BIT(rc, probs + m, bit);
    rc->range = range;
  }
}
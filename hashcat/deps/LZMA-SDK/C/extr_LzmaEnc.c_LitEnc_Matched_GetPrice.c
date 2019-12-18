#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int UInt32 ;
typedef  int /*<<< orphan*/  CProbPrice ;
typedef  int /*<<< orphan*/  CLzmaProb ;

/* Variables and functions */
 scalar_t__ GET_PRICEa (int /*<<< orphan*/  const,int) ; 

__attribute__((used)) static UInt32 LitEnc_Matched_GetPrice(const CLzmaProb *probs, UInt32 sym, UInt32 matchByte, const CProbPrice *ProbPrices)
{
  UInt32 price = 0;
  UInt32 offs = 0x100;
  sym |= 0x100;
  do
  {
    matchByte <<= 1;
    price += GET_PRICEa(probs[offs + (matchByte & offs) + (sym >> 8)], (sym >> 7) & 1);
    sym <<= 1;
    offs &= ~(matchByte ^ sym);
  }
  while (sym < 0x10000);
  return price;
}
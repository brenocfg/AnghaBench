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
typedef  int UInt32 ;
struct TYPE_3__ {unsigned int* posEncoders; int distTableSize; int** posSlotPrices; unsigned int** posSlotEncoder; int** distancesPrices; scalar_t__ matchPriceCount; int /*<<< orphan*/ * ProbPrices; } ;
typedef  int /*<<< orphan*/  CProbPrice ;
typedef  unsigned int CLzmaProb ;
typedef  TYPE_1__ CLzmaEnc ;

/* Variables and functions */
 int GET_PRICEa (unsigned int const,unsigned int) ; 
 int GET_PRICEa_0 (unsigned int) ; 
 int GET_PRICEa_1 (unsigned int) ; 
 size_t GetPosSlot1 (unsigned int) ; 
 int kEndPosModelIndex ; 
 int kNumAlignBits ; 
 int kNumBitPriceShiftBits ; 
 int kNumFullDistances ; 
 unsigned int kNumLenToPosStates ; 
 int kNumPosSlotBits ; 
 int kStartPosModelIndex ; 

__attribute__((used)) static void FillDistancesPrices(CLzmaEnc *p)
{
  // int y; for (y = 0; y < 100; y++) {

  UInt32 tempPrices[kNumFullDistances];
  unsigned i, lps;

  const CProbPrice *ProbPrices = p->ProbPrices;
  p->matchPriceCount = 0;

  for (i = kStartPosModelIndex / 2; i < kNumFullDistances / 2; i++)
  {
    unsigned posSlot = GetPosSlot1(i);
    unsigned footerBits = (posSlot >> 1) - 1;
    unsigned base = ((2 | (posSlot & 1)) << footerBits);
    const CLzmaProb *probs = p->posEncoders + (size_t)base * 2;
    // tempPrices[i] = RcTree_ReverseGetPrice(p->posEncoders + base, footerBits, i - base, p->ProbPrices);
    UInt32 price = 0;
    unsigned m = 1;
    unsigned sym = i;
    unsigned offset = (unsigned)1 << footerBits;
    base += i;
    
    if (footerBits)
    do
    {
      unsigned bit = sym & 1;
      sym >>= 1;
      price += GET_PRICEa(probs[m], bit);
      m = (m << 1) + bit;
    }
    while (--footerBits);

    {
      unsigned prob = probs[m];
      tempPrices[base         ] = price + GET_PRICEa_0(prob);
      tempPrices[base + offset] = price + GET_PRICEa_1(prob);
    }
  }

  for (lps = 0; lps < kNumLenToPosStates; lps++)
  {
    unsigned slot;
    unsigned distTableSize2 = (p->distTableSize + 1) >> 1;
    UInt32 *posSlotPrices = p->posSlotPrices[lps];
    const CLzmaProb *probs = p->posSlotEncoder[lps];
    
    for (slot = 0; slot < distTableSize2; slot++)
    {
      // posSlotPrices[slot] = RcTree_GetPrice(encoder, kNumPosSlotBits, slot, p->ProbPrices);
      UInt32 price;
      unsigned bit;
      unsigned sym = slot + (1 << (kNumPosSlotBits - 1));
      unsigned prob;
      bit = sym & 1; sym >>= 1; price  = GET_PRICEa(probs[sym], bit);
      bit = sym & 1; sym >>= 1; price += GET_PRICEa(probs[sym], bit);
      bit = sym & 1; sym >>= 1; price += GET_PRICEa(probs[sym], bit);
      bit = sym & 1; sym >>= 1; price += GET_PRICEa(probs[sym], bit);
      bit = sym & 1; sym >>= 1; price += GET_PRICEa(probs[sym], bit);
      prob = probs[(size_t)slot + (1 << (kNumPosSlotBits - 1))];
      posSlotPrices[(size_t)slot * 2    ] = price + GET_PRICEa_0(prob);
      posSlotPrices[(size_t)slot * 2 + 1] = price + GET_PRICEa_1(prob);
    }
    
    {
      UInt32 delta = ((UInt32)((kEndPosModelIndex / 2 - 1) - kNumAlignBits) << kNumBitPriceShiftBits);
      for (slot = kEndPosModelIndex / 2; slot < distTableSize2; slot++)
      {
        posSlotPrices[(size_t)slot * 2    ] += delta;
        posSlotPrices[(size_t)slot * 2 + 1] += delta;
        delta += ((UInt32)1 << kNumBitPriceShiftBits);
      }
    }

    {
      UInt32 *dp = p->distancesPrices[lps];
      
      dp[0] = posSlotPrices[0];
      dp[1] = posSlotPrices[1];
      dp[2] = posSlotPrices[2];
      dp[3] = posSlotPrices[3];

      for (i = 4; i < kNumFullDistances; i += 2)
      {
        UInt32 slotPrice = posSlotPrices[GetPosSlot1(i)];
        dp[i    ] = slotPrice + tempPrices[i];
        dp[i + 1] = slotPrice + tempPrices[i + 1];
      }
    }
  }
  // }
}
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
struct TYPE_3__ {int* posEncoders; int** posSlotEncoder; int** posSlotPrices; unsigned int distTableSize; int** distancesPrices; scalar_t__ matchPriceCount; int /*<<< orphan*/ * ProbPrices; } ;
typedef  int /*<<< orphan*/  CProbPrice ;
typedef  int CLzmaProb ;
typedef  TYPE_1__ CLzmaEnc ;

/* Variables and functions */
 int GET_PRICEa (int const,unsigned int) ; 
 int GET_PRICEa_0 (int) ; 
 int GET_PRICEa_1 (int) ; 
 size_t GetPosSlot1 (unsigned int) ; 
 unsigned int kEndPosModelIndex ; 
 unsigned int kNumAlignBits ; 
 int kNumBitPriceShiftBits ; 
 int kNumFullDistances ; 
 unsigned int kNumLenToPosStates ; 
 int kNumPosSlotBits ; 
 unsigned int kStartPosModelIndex ; 

__attribute__((used)) static void FillDistancesPrices(CLzmaEnc *p)
{
  UInt32 tempPrices[kNumFullDistances];
  unsigned i, lenToPosState;

  const CProbPrice *ProbPrices = p->ProbPrices;
  p->matchPriceCount = 0;

  for (i = kStartPosModelIndex; i < kNumFullDistances; i++)
  {
    unsigned posSlot = GetPosSlot1(i);
    unsigned footerBits = ((posSlot >> 1) - 1);
    unsigned base = ((2 | (posSlot & 1)) << footerBits);
    // tempPrices[i] = RcTree_ReverseGetPrice(p->posEncoders + base, footerBits, i - base, p->ProbPrices);

    const CLzmaProb *probs = p->posEncoders + base;
    UInt32 price = 0;
    unsigned m = 1;
    unsigned symbol = i - base;
    do
    {
      unsigned bit = symbol & 1;
      symbol >>= 1;
      price += GET_PRICEa(probs[m], bit);
      m = (m << 1) + bit;
    }
    while (--footerBits);
    tempPrices[i] = price;
  }

  for (lenToPosState = 0; lenToPosState < kNumLenToPosStates; lenToPosState++)
  {
    unsigned posSlot;
    const CLzmaProb *encoder = p->posSlotEncoder[lenToPosState];
    UInt32 *posSlotPrices = p->posSlotPrices[lenToPosState];
    unsigned distTableSize = p->distTableSize;
    const CLzmaProb *probs = encoder;
    for (posSlot = 0; posSlot < distTableSize; posSlot += 2)
    {
      // posSlotPrices[posSlot] = RcTree_GetPrice(encoder, kNumPosSlotBits, posSlot, p->ProbPrices);
      UInt32 price = 0;
      unsigned bit;
      unsigned symbol = (posSlot >> 1) + (1 << (kNumPosSlotBits - 1));
      UInt32 prob;
      bit = symbol & 1; symbol >>= 1; price += GET_PRICEa(probs[symbol], bit);
      bit = symbol & 1; symbol >>= 1; price += GET_PRICEa(probs[symbol], bit);
      bit = symbol & 1; symbol >>= 1; price += GET_PRICEa(probs[symbol], bit);
      bit = symbol & 1; symbol >>= 1; price += GET_PRICEa(probs[symbol], bit);
      bit = symbol & 1; symbol >>= 1; price += GET_PRICEa(probs[symbol], bit);
      prob = probs[(posSlot >> 1) + (1 << (kNumPosSlotBits - 1))];
      posSlotPrices[posSlot    ] = price + GET_PRICEa_0(prob);
      posSlotPrices[posSlot + 1] = price + GET_PRICEa_1(prob);
    }
    for (posSlot = kEndPosModelIndex; posSlot < distTableSize; posSlot++)
      posSlotPrices[posSlot] += ((UInt32)(((posSlot >> 1) - 1) - kNumAlignBits) << kNumBitPriceShiftBits);

    {
      UInt32 *distancesPrices = p->distancesPrices[lenToPosState];
      {
        distancesPrices[0] = posSlotPrices[0];
        distancesPrices[1] = posSlotPrices[1];
        distancesPrices[2] = posSlotPrices[2];
        distancesPrices[3] = posSlotPrices[3];
      }
      for (i = 4; i < kNumFullDistances; i += 2)
      {
        UInt32 slotPrice = posSlotPrices[GetPosSlot1(i)];
        distancesPrices[i    ] = slotPrice + tempPrices[i];
        distancesPrices[i + 1] = slotPrice + tempPrices[i + 1];
      }
    }
  }
}
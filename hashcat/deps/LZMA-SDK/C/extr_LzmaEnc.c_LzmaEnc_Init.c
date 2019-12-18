#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UInt32 ;
struct TYPE_5__ {int* reps; size_t lp; size_t lc; int pbMask; int pb; size_t lpMask; scalar_t__ additionalOffset; TYPE_1__* opt; scalar_t__ optCur; scalar_t__ optEnd; int /*<<< orphan*/  repLenProbs; int /*<<< orphan*/  lenProbs; void** litProbs; void** posEncoders; void*** posSlotEncoder; void** isRepG2; void** isRepG1; void** isRepG0; void** isRep; void*** isRep0Long; void*** isMatch; void** posAlignEncoder; int /*<<< orphan*/  rc; scalar_t__ state; } ;
struct TYPE_4__ {int /*<<< orphan*/  price; } ;
typedef  void* CLzmaProb ;
typedef  TYPE_2__ CLzmaEnc ;

/* Variables and functions */
 unsigned int LZMA_NUM_PB_STATES_MAX ; 
 int /*<<< orphan*/  LenEnc_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RangeEnc_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kInfinityPrice ; 
 int kNumAlignBits ; 
 unsigned int kNumFullDistances ; 
 unsigned int kNumLenToPosStates ; 
 unsigned int kNumOpts ; 
 int kNumPosSlotBits ; 
 unsigned int kNumStates ; 
 void* kProbInitValue ; 

void LzmaEnc_Init(CLzmaEnc *p)
{
  unsigned i;
  p->state = 0;
  p->reps[0] =
  p->reps[1] =
  p->reps[2] =
  p->reps[3] = 1;

  RangeEnc_Init(&p->rc);

  for (i = 0; i < (1 << kNumAlignBits); i++)
    p->posAlignEncoder[i] = kProbInitValue;

  for (i = 0; i < kNumStates; i++)
  {
    unsigned j;
    for (j = 0; j < LZMA_NUM_PB_STATES_MAX; j++)
    {
      p->isMatch[i][j] = kProbInitValue;
      p->isRep0Long[i][j] = kProbInitValue;
    }
    p->isRep[i] = kProbInitValue;
    p->isRepG0[i] = kProbInitValue;
    p->isRepG1[i] = kProbInitValue;
    p->isRepG2[i] = kProbInitValue;
  }

  {
    for (i = 0; i < kNumLenToPosStates; i++)
    {
      CLzmaProb *probs = p->posSlotEncoder[i];
      unsigned j;
      for (j = 0; j < (1 << kNumPosSlotBits); j++)
        probs[j] = kProbInitValue;
    }
  }
  {
    for (i = 0; i < kNumFullDistances; i++)
      p->posEncoders[i] = kProbInitValue;
  }

  {
    UInt32 num = (UInt32)0x300 << (p->lp + p->lc);
    UInt32 k;
    CLzmaProb *probs = p->litProbs;
    for (k = 0; k < num; k++)
      probs[k] = kProbInitValue;
  }


  LenEnc_Init(&p->lenProbs);
  LenEnc_Init(&p->repLenProbs);

  p->optEnd = 0;
  p->optCur = 0;

  {
    for (i = 0; i < kNumOpts; i++)
      p->opt[i].price = kInfinityPrice;
  }

  p->additionalOffset = 0;

  p->pbMask = (1 << p->pb) - 1;
  p->lpMask = ((UInt32)0x100 << p->lp) - ((unsigned)0x100 >> p->lc);
}
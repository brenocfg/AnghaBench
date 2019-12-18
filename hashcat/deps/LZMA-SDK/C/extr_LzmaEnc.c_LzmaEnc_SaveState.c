#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt32 ;
struct TYPE_5__ {int /*<<< orphan*/  litProbs; int /*<<< orphan*/  repLenProbs; int /*<<< orphan*/  lenProbs; int /*<<< orphan*/  state; } ;
struct TYPE_6__ {int lclp; int /*<<< orphan*/  litProbs; int /*<<< orphan*/  repLenProbs; int /*<<< orphan*/  lenProbs; int /*<<< orphan*/  state; TYPE_1__ saveState; } ;
typedef  TYPE_1__ CSaveState ;
typedef  int /*<<< orphan*/  CLzmaProb ;
typedef  scalar_t__ CLzmaEncHandle ;
typedef  TYPE_2__ CLzmaEnc ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_ARR (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isMatch ; 
 int /*<<< orphan*/  isRep ; 
 int /*<<< orphan*/  isRep0Long ; 
 int /*<<< orphan*/  isRepG0 ; 
 int /*<<< orphan*/  isRepG1 ; 
 int /*<<< orphan*/  isRepG2 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  posAlignEncoder ; 
 int /*<<< orphan*/  posEncoders ; 
 int /*<<< orphan*/  posSlotEncoder ; 
 int /*<<< orphan*/  reps ; 

void LzmaEnc_SaveState(CLzmaEncHandle pp)
{
  CLzmaEnc *p = (CLzmaEnc *)pp;
  CSaveState *dest = &p->saveState;
  
  dest->state = p->state;
  
  dest->lenProbs = p->lenProbs;
  dest->repLenProbs = p->repLenProbs;

  COPY_ARR(dest, p, reps);

  COPY_ARR(dest, p, posAlignEncoder);
  COPY_ARR(dest, p, isRep);
  COPY_ARR(dest, p, isRepG0);
  COPY_ARR(dest, p, isRepG1);
  COPY_ARR(dest, p, isRepG2);
  COPY_ARR(dest, p, isMatch);
  COPY_ARR(dest, p, isRep0Long);
  COPY_ARR(dest, p, posSlotEncoder);
  COPY_ARR(dest, p, posEncoders);

  memcpy(dest->litProbs, p->litProbs, ((UInt32)0x300 << p->lclp) * sizeof(CLzmaProb));
}
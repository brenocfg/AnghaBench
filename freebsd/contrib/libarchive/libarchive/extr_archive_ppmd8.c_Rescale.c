#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int UInt16 ;
struct TYPE_13__ {unsigned int SummFreq; unsigned int NumStats; int Flags; int /*<<< orphan*/  Stats; } ;
struct TYPE_12__ {scalar_t__ OrderFall; scalar_t__ RestoreMethod; TYPE_5__* MinContext; TYPE_1__* FoundState; } ;
struct TYPE_11__ {int Freq; int Symbol; } ;
typedef  TYPE_1__ CPpmd_State ;
typedef  TYPE_2__ CPpmd8 ;
typedef  void* Byte ;

/* Variables and functions */
 int /*<<< orphan*/  InsertNode (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int MAX_FREQ ; 
 TYPE_1__* ONE_STATE (TYPE_5__*) ; 
 scalar_t__ PPMD8_RESTORE_METHOD_FREEZE ; 
 void* STATS (TYPE_5__*) ; 
 int /*<<< orphan*/  STATS_REF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShrinkUnits (TYPE_2__*,TYPE_1__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  U2I (unsigned int) ; 

__attribute__((used)) static void Rescale(CPpmd8 *p)
{
  unsigned i, adder, sumFreq, escFreq;
  CPpmd_State *stats = STATS(p->MinContext);
  CPpmd_State *s = p->FoundState;
  {
    CPpmd_State tmp = *s;
    for (; s != stats; s--)
      s[0] = s[-1];
    *s = tmp;
  }
  escFreq = p->MinContext->SummFreq - s->Freq;
  s->Freq += 4;
  adder = (p->OrderFall != 0
      #ifdef PPMD8_FREEZE_SUPPORT
      || p->RestoreMethod > PPMD8_RESTORE_METHOD_FREEZE
      #endif
      );
  s->Freq = (Byte)((s->Freq + adder) >> 1);
  sumFreq = s->Freq;
  
  i = p->MinContext->NumStats;
  do
  {
    escFreq -= (++s)->Freq;
    s->Freq = (Byte)((s->Freq + adder) >> 1);
    sumFreq += s->Freq;
    if (s[0].Freq > s[-1].Freq)
    {
      CPpmd_State *s1 = s;
      CPpmd_State tmp = *s1;
      do
        s1[0] = s1[-1];
      while (--s1 != stats && tmp.Freq > s1[-1].Freq);
      *s1 = tmp;
    }
  }
  while (--i);
  
  if (s->Freq == 0)
  {
    unsigned numStats = p->MinContext->NumStats;
    unsigned n0, n1;
    do { i++; } while ((--s)->Freq == 0);
    escFreq += i;
    p->MinContext->NumStats = (Byte)(p->MinContext->NumStats - i);
    if (p->MinContext->NumStats == 0)
    {
      CPpmd_State tmp = *stats;
      tmp.Freq = (Byte)((2 * tmp.Freq + escFreq - 1) / escFreq);
      if (tmp.Freq > MAX_FREQ / 3)
        tmp.Freq = MAX_FREQ / 3;
      InsertNode(p, stats, U2I((numStats + 2) >> 1));
      p->MinContext->Flags = (Byte)((p->MinContext->Flags & 0x10) + 0x08 * (tmp.Symbol >= 0x40));
      *(p->FoundState = ONE_STATE(p->MinContext)) = tmp;
      return;
    }
    n0 = (numStats + 2) >> 1;
    n1 = (p->MinContext->NumStats + 2) >> 1;
    if (n0 != n1)
      p->MinContext->Stats = STATS_REF(ShrinkUnits(p, stats, n0, n1));
    p->MinContext->Flags &= ~0x08;
    p->MinContext->Flags |= 0x08 * ((s = STATS(p->MinContext))->Symbol >= 0x40);
    i = p->MinContext->NumStats;
    do { p->MinContext->Flags |= 0x08*((++s)->Symbol >= 0x40); } while (--i);
  }
  p->MinContext->SummFreq = (UInt16)(sumFreq + escFreq - (escFreq >> 1));
  p->MinContext->Flags |= 0x4;
  p->FoundState = STATS(p->MinContext);
}
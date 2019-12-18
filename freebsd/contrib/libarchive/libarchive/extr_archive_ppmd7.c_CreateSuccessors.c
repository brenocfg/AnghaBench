#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt32 ;
struct TYPE_21__ {scalar_t__ HiUnit; scalar_t__ LoUnit; scalar_t__* FreeList; TYPE_2__* FoundState; TYPE_1__* MinContext; } ;
struct TYPE_20__ {scalar_t__ Symbol; int Freq; } ;
struct TYPE_19__ {int NumStats; int SummFreq; scalar_t__ Suffix; } ;
typedef  TYPE_1__* CTX_PTR ;
typedef  scalar_t__ CPpmd_Void_Ref ;
typedef  TYPE_2__ CPpmd_State ;
typedef  scalar_t__ CPpmd_Byte_Ref ;
typedef  TYPE_3__ CPpmd7 ;
typedef  int Byte ;
typedef  int /*<<< orphan*/  Bool ;

/* Variables and functions */
 scalar_t__ AllocUnitsRare (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* CTX (scalar_t__) ; 
 TYPE_2__* ONE_STATE (TYPE_1__*) ; 
 int PPMD7_MAX_ORDER ; 
 scalar_t__ Ppmd7_GetPtr (TYPE_3__*,scalar_t__) ; 
 scalar_t__ REF (TYPE_1__*) ; 
 scalar_t__ RemoveNode (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* STATS (TYPE_1__*) ; 
 scalar_t__ SUCCESSOR (TYPE_2__*) ; 
 TYPE_1__* SUFFIX (TYPE_1__*) ; 
 int /*<<< orphan*/  SetSuccessor (TYPE_2__*,scalar_t__) ; 
 scalar_t__ UNIT_SIZE ; 

__attribute__((used)) static CTX_PTR CreateSuccessors(CPpmd7 *p, Bool skip)
{
  CPpmd_State upState;
  CTX_PTR c = p->MinContext;
  CPpmd_Byte_Ref upBranch = (CPpmd_Byte_Ref)SUCCESSOR(p->FoundState);
  CPpmd_State *ps[PPMD7_MAX_ORDER];
  unsigned numPs = 0;
  
  if (!skip)
    ps[numPs++] = p->FoundState;
  
  while (c->Suffix)
  {
    CPpmd_Void_Ref successor;
    CPpmd_State *s;
    c = SUFFIX(c);
    if (c->NumStats != 1)
    {
      for (s = STATS(c); s->Symbol != p->FoundState->Symbol; s++);
    }
    else
      s = ONE_STATE(c);
    successor = SUCCESSOR(s);
    if (successor != upBranch)
    {
      c = CTX(successor);
      if (numPs == 0)
        return c;
      break;
    }
    ps[numPs++] = s;
  }
  
  upState.Symbol = *(const Byte *)Ppmd7_GetPtr(p, upBranch);
  SetSuccessor(&upState, upBranch + 1);
  
  if (c->NumStats == 1)
    upState.Freq = ONE_STATE(c)->Freq;
  else
  {
    UInt32 cf, s0;
    CPpmd_State *s;
    for (s = STATS(c); s->Symbol != upState.Symbol; s++);
    cf = s->Freq - 1;
    s0 = c->SummFreq - c->NumStats - cf;
    upState.Freq = (Byte)(1 + ((2 * cf <= s0) ? (5 * cf > s0) : ((2 * cf + 3 * s0 - 1) / (2 * s0))));
  }

  while (numPs != 0)
  {
    /* Create Child */
    CTX_PTR c1; /* = AllocContext(p); */
    if (p->HiUnit != p->LoUnit)
      c1 = (CTX_PTR)(p->HiUnit -= UNIT_SIZE);
    else if (p->FreeList[0] != 0)
      c1 = (CTX_PTR)RemoveNode(p, 0);
    else
    {
      c1 = (CTX_PTR)AllocUnitsRare(p, 0);
      if (!c1)
        return NULL;
    }
    c1->NumStats = 1;
    *ONE_STATE(c1) = upState;
    c1->Suffix = REF(c);
    SetSuccessor(ps[--numPs], REF(c1));
    c = c1;
  }
  
  return c;
}
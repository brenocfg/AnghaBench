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
struct TYPE_6__ {int numHashBytes; int /*<<< orphan*/  btMode; } ;
struct TYPE_5__ {void* Skip; void* GetMatches; scalar_t__ GetPointerToCurrentPos; scalar_t__ GetNumAvailableBytes; scalar_t__ Init; } ;
typedef  void* Mf_Skip_Func ;
typedef  scalar_t__ Mf_Init_Func ;
typedef  scalar_t__ Mf_GetPointerToCurrentPos_Func ;
typedef  scalar_t__ Mf_GetNumAvailableBytes_Func ;
typedef  void* Mf_GetMatches_Func ;
typedef  TYPE_1__ IMatchFinder ;
typedef  TYPE_2__ CMatchFinder ;

/* Variables and functions */
 scalar_t__ Bt2_MatchFinder_GetMatches ; 
 scalar_t__ Bt2_MatchFinder_Skip ; 
 scalar_t__ Bt3_MatchFinder_GetMatches ; 
 scalar_t__ Bt3_MatchFinder_Skip ; 
 scalar_t__ Bt4_MatchFinder_GetMatches ; 
 scalar_t__ Bt4_MatchFinder_Skip ; 
 scalar_t__ Hc4_MatchFinder_GetMatches ; 
 scalar_t__ Hc4_MatchFinder_Skip ; 
 scalar_t__ MatchFinder_GetNumAvailableBytes ; 
 scalar_t__ MatchFinder_GetPointerToCurrentPos ; 
 scalar_t__ MatchFinder_Init ; 

void MatchFinder_CreateVTable(CMatchFinder *p, IMatchFinder *vTable)
{
  vTable->Init = (Mf_Init_Func)MatchFinder_Init;
  vTable->GetNumAvailableBytes = (Mf_GetNumAvailableBytes_Func)MatchFinder_GetNumAvailableBytes;
  vTable->GetPointerToCurrentPos = (Mf_GetPointerToCurrentPos_Func)MatchFinder_GetPointerToCurrentPos;
  if (!p->btMode)
  {
    /* if (p->numHashBytes <= 4) */
    {
      vTable->GetMatches = (Mf_GetMatches_Func)Hc4_MatchFinder_GetMatches;
      vTable->Skip = (Mf_Skip_Func)Hc4_MatchFinder_Skip;
    }
    /*
    else
    {
      vTable->GetMatches = (Mf_GetMatches_Func)Hc5_MatchFinder_GetMatches;
      vTable->Skip = (Mf_Skip_Func)Hc5_MatchFinder_Skip;
    }
    */
  }
  else if (p->numHashBytes == 2)
  {
    vTable->GetMatches = (Mf_GetMatches_Func)Bt2_MatchFinder_GetMatches;
    vTable->Skip = (Mf_Skip_Func)Bt2_MatchFinder_Skip;
  }
  else if (p->numHashBytes == 3)
  {
    vTable->GetMatches = (Mf_GetMatches_Func)Bt3_MatchFinder_GetMatches;
    vTable->Skip = (Mf_Skip_Func)Bt3_MatchFinder_Skip;
  }
  else /* if (p->numHashBytes == 4) */
  {
    vTable->GetMatches = (Mf_GetMatches_Func)Bt4_MatchFinder_GetMatches;
    vTable->Skip = (Mf_Skip_Func)Bt4_MatchFinder_Skip;
  }
  /*
  else
  {
    vTable->GetMatches = (Mf_GetMatches_Func)Bt5_MatchFinder_GetMatches;
    vTable->Skip = (Mf_Skip_Func)Bt5_MatchFinder_Skip;
  }
  */
}
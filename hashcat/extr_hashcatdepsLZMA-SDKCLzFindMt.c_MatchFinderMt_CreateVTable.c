#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* MixMatchesFunc; TYPE_1__* MatchFinder; int /*<<< orphan*/  GetHeadsFunc; } ;
struct TYPE_7__ {void* Skip; void* GetMatches; scalar_t__ GetPointerToCurrentPos; scalar_t__ GetNumAvailableBytes; scalar_t__ Init; } ;
struct TYPE_6__ {int numHashBytes; int /*<<< orphan*/  bigHash; } ;
typedef  void* Mf_Skip_Func ;
typedef  void* Mf_Mix_Matches ;
typedef  scalar_t__ Mf_Init_Func ;
typedef  scalar_t__ Mf_GetPointerToCurrentPos_Func ;
typedef  scalar_t__ Mf_GetNumAvailableBytes_Func ;
typedef  void* Mf_GetMatches_Func ;
typedef  TYPE_2__ IMatchFinder ;
typedef  TYPE_3__ CMatchFinderMt ;

/* Variables and functions */
 int /*<<< orphan*/  GetHeads2 ; 
 int /*<<< orphan*/  GetHeads3 ; 
 int /*<<< orphan*/  GetHeads4 ; 
 int /*<<< orphan*/  GetHeads4b ; 
 int /*<<< orphan*/  MatchFinderMt0_Skip ; 
 scalar_t__ MatchFinderMt2_GetMatches ; 
 int /*<<< orphan*/  MatchFinderMt2_Skip ; 
 int /*<<< orphan*/  MatchFinderMt3_Skip ; 
 scalar_t__ MatchFinderMt_GetMatches ; 
 scalar_t__ MatchFinderMt_GetNumAvailableBytes ; 
 scalar_t__ MatchFinderMt_GetPointerToCurrentPos ; 
 scalar_t__ MatchFinderMt_Init ; 
 int /*<<< orphan*/  MixMatches2 ; 
 int /*<<< orphan*/  MixMatches3 ; 

void MatchFinderMt_CreateVTable(CMatchFinderMt *p, IMatchFinder *vTable)
{
  vTable->Init = (Mf_Init_Func)MatchFinderMt_Init;
  vTable->GetNumAvailableBytes = (Mf_GetNumAvailableBytes_Func)MatchFinderMt_GetNumAvailableBytes;
  vTable->GetPointerToCurrentPos = (Mf_GetPointerToCurrentPos_Func)MatchFinderMt_GetPointerToCurrentPos;
  vTable->GetMatches = (Mf_GetMatches_Func)MatchFinderMt_GetMatches;
  
  switch (p->MatchFinder->numHashBytes)
  {
    case 2:
      p->GetHeadsFunc = GetHeads2;
      p->MixMatchesFunc = (Mf_Mix_Matches)NULL;
      vTable->Skip = (Mf_Skip_Func)MatchFinderMt0_Skip;
      vTable->GetMatches = (Mf_GetMatches_Func)MatchFinderMt2_GetMatches;
      break;
    case 3:
      p->GetHeadsFunc = GetHeads3;
      p->MixMatchesFunc = (Mf_Mix_Matches)MixMatches2;
      vTable->Skip = (Mf_Skip_Func)MatchFinderMt2_Skip;
      break;
    default:
    /* case 4: */
      p->GetHeadsFunc = p->MatchFinder->bigHash ? GetHeads4b : GetHeads4;
      p->MixMatchesFunc = (Mf_Mix_Matches)MixMatches3;
      vTable->Skip = (Mf_Skip_Func)MatchFinderMt3_Skip;
      break;
    /*
    default:
      p->GetHeadsFunc = GetHeads5;
      p->MixMatchesFunc = (Mf_Mix_Matches)MixMatches4;
      vTable->Skip = (Mf_Skip_Func)MatchFinderMt4_Skip;
      break;
    */
  }
}
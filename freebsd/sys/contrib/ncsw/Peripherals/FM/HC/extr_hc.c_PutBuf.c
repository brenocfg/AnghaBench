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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  t_HcFrame ;
struct TYPE_3__ {size_t nextSeqNumLocation; int /*<<< orphan*/  h_FmPcd; int /*<<< orphan*/ * seqNum; } ;
typedef  TYPE_1__ t_FmHc ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (size_t) ; 
 int /*<<< orphan*/  FmPcdLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdUnlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline__ void PutBuf(t_FmHc *p_FmHc, t_HcFrame *p_Buf, uint32_t seqNum)
{
    uint32_t    intFlags;

    UNUSED(p_Buf);

    intFlags = FmPcdLock(p_FmHc->h_FmPcd);
    ASSERT_COND(p_FmHc->nextSeqNumLocation);
    p_FmHc->nextSeqNumLocation--;
    p_FmHc->seqNum[p_FmHc->nextSeqNumLocation] = seqNum;
    FmPcdUnlock(p_FmHc->h_FmPcd, intFlags);
}
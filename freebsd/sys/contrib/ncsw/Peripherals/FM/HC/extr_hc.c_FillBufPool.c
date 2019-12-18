#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  t_HcFrame ;
struct TYPE_4__ {size_t* seqNum; scalar_t__ nextSeqNumLocation; int /*<<< orphan*/ ** p_Frm; int /*<<< orphan*/  dataMemId; } ;
typedef  TYPE_1__ t_FmHc ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  E_OK ; 
 size_t HC_CMD_POOL_SIZE ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ XX_MallocSmart (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static t_Error FillBufPool(t_FmHc *p_FmHc)
{
    uint32_t i;

    ASSERT_COND(p_FmHc);

    for (i = 0; i < HC_CMD_POOL_SIZE; i++)
    {
#ifdef FM_LOCKUP_ALIGNMENT_ERRATA_FMAN_SW004
        p_FmHc->p_Frm[i] = (t_HcFrame *)XX_MallocSmart((sizeof(t_HcFrame) + (16 - (sizeof(t_FmHc) % 16))),
                                                       p_FmHc->dataMemId,
                                                       16);
#else
        p_FmHc->p_Frm[i] = (t_HcFrame *)XX_MallocSmart(sizeof(t_HcFrame),
                                                       p_FmHc->dataMemId,
                                                       16);
#endif /* FM_LOCKUP_ALIGNMENT_ERRATA_FMAN_SW004 */
        if (!p_FmHc->p_Frm[i])
            RETURN_ERROR(MAJOR, E_NO_MEMORY, ("FM HC frames!"));
    }

    /* Initialize FIFO of seqNum to use during GetBuf */
    for (i = 0; i < HC_CMD_POOL_SIZE; i++)
    {
        p_FmHc->seqNum[i] = i;
    }
    p_FmHc->nextSeqNumLocation = 0;

    return E_OK;
}
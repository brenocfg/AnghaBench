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
typedef  size_t uint32_t ;
struct TYPE_3__ {scalar_t__* enqueued; int /*<<< orphan*/  h_QmArg; scalar_t__ (* f_QmEnqueue ) (int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  h_FmPcd; } ;
typedef  TYPE_1__ t_FmHc ;
typedef  scalar_t__ t_Error ;
typedef  int /*<<< orphan*/  t_DpaaFD ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DPAA_FD_GET_ADDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPAA_FD_GET_OFFSET (int /*<<< orphan*/ *) ; 
 scalar_t__ E_OK ; 
 scalar_t__ E_TIMEOUT ; 
 size_t FmPcdLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdUnlock (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  MINOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  TRACE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  XX_UDelay (int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static __inline__ t_Error EnQFrm(t_FmHc *p_FmHc, t_DpaaFD *p_FmFd, uint32_t seqNum)
{
    t_Error     err = E_OK;
    uint32_t    intFlags;
    uint32_t    timeout=100;

    intFlags = FmPcdLock(p_FmHc->h_FmPcd);
    ASSERT_COND(!p_FmHc->enqueued[seqNum]);
    p_FmHc->enqueued[seqNum] = TRUE;
    FmPcdUnlock(p_FmHc->h_FmPcd, intFlags);
    DBG(TRACE, ("Send Hc, SeqNum %d, buff@0x%x, fd offset 0x%x",
                seqNum,
                DPAA_FD_GET_ADDR(p_FmFd),
                DPAA_FD_GET_OFFSET(p_FmFd)));
    err = p_FmHc->f_QmEnqueue(p_FmHc->h_QmArg, (void *)p_FmFd);
    if (err)
        RETURN_ERROR(MINOR, err, ("HC enqueue failed"));

    while (p_FmHc->enqueued[seqNum] && --timeout)
        XX_UDelay(100);

    if (!timeout)
        RETURN_ERROR(MINOR, E_TIMEOUT, ("HC Callback, timeout exceeded"));

    return err;
}
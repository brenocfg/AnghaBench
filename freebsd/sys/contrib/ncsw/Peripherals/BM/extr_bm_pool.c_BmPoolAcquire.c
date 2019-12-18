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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  t_Handle ;
struct TYPE_3__ {int flags; int spFill; int spMinBufs; int spBufsCmd; int /*<<< orphan*/  sp; int /*<<< orphan*/  bpid; } ;
typedef  TYPE_1__ t_BmPool ;
struct bm_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int /*<<< orphan*/ ) ; 
 int BMAN_ACQUIRE_FLAG_STOCKPILE ; 
 int BMAN_POOL_FLAG_ONLY_RELEASE ; 
 int BMAN_POOL_FLAG_STOCKPILE ; 
 int BmPortalAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bm_buffer*,int) ; 
 int /*<<< orphan*/  IN_RANGE (int,int,int) ; 
 scalar_t__ PTR_MOVE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct bm_buffer*,scalar_t__,int) ; 

__attribute__((used)) static int BmPoolAcquire(t_BmPool *p_BmPool,t_Handle h_BmPortal,
            struct bm_buffer *bufs, uint8_t num, uint32_t flags)
{
    ASSERT_COND(IN_RANGE(1, num, 8));
    if (p_BmPool->flags & BMAN_POOL_FLAG_ONLY_RELEASE)
        return 0;

    /* Without stockpile, this API is a pass-through to the h/w operation */
    if (!(p_BmPool->flags & BMAN_POOL_FLAG_STOCKPILE))
        return BmPortalAcquire(h_BmPortal, p_BmPool->bpid, bufs, num);
    /* Only need a h/w op if we'll hit the low-water thresh */
    if (!(flags & BMAN_ACQUIRE_FLAG_STOCKPILE) &&
            ((p_BmPool->spFill - num) < p_BmPool->spMinBufs))
    {
            p_BmPool->spFill += BmPortalAcquire(h_BmPortal,
                                               p_BmPool->bpid,
                                               (struct bm_buffer *)PTR_MOVE(p_BmPool->sp, sizeof(struct bm_buffer) * (p_BmPool->spFill)),
                                               p_BmPool->spBufsCmd);
    }
    else if (p_BmPool->spFill < num)
        return 0;
    if (!p_BmPool->spFill)
        return 0;
    memcpy(bufs,
           PTR_MOVE(p_BmPool->sp, sizeof(struct bm_buffer) * (p_BmPool->spFill - num)),
           sizeof(struct bm_buffer) * num);
    p_BmPool->spFill -= num;
    return num;
}
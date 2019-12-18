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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  t_Handle ;
typedef  scalar_t__ t_Error ;
struct TYPE_3__ {int flags; int spFill; int spMaxBufs; int spBufsCmd; int /*<<< orphan*/  sp; int /*<<< orphan*/  bpid; } ;
typedef  TYPE_1__ t_BmPool ;
struct bm_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int BMAN_POOL_FLAG_NO_RELEASE ; 
 int BMAN_POOL_FLAG_STOCKPILE ; 
 scalar_t__ BmPortalRelease (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bm_buffer*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 scalar_t__ E_OK ; 
 scalar_t__ PTR_MOVE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct bm_buffer*,int) ; 

__attribute__((used)) static t_Error BmPoolRelease(t_BmPool *p_BmPool,
                             t_Handle h_BmPortal,
                             struct bm_buffer *bufs,
                             uint8_t num,
                             uint32_t flags)
{
    ASSERT_COND(num && (num <= 8));
    if (p_BmPool->flags & BMAN_POOL_FLAG_NO_RELEASE)
        return ERROR_CODE(E_INVALID_VALUE);

    /* Without stockpile, this API is a pass-through to the h/w operation */
    if (!(p_BmPool->flags & BMAN_POOL_FLAG_STOCKPILE))
        return BmPortalRelease(h_BmPortal, p_BmPool->bpid, bufs, num, flags);

    /* This needs some explanation. Adding the given buffers may take the
     * stockpile over the threshold, but in fact the stockpile may already
     * *be* over the threshold if a previous release-to-hw attempt had
     * failed. So we have 3 cases to cover;
     *   1. we add to the stockpile and don't hit the threshold,
     *   2. we add to the stockpile, hit the threshold and release-to-hw,
     *   3. we have to release-to-hw before adding to the stockpile
     *      (not enough room in the stockpile for case 2).
     * Our constraints on thresholds guarantee that in case 3, there must be
     * at least 8 bufs already in the stockpile, so all release-to-hw ops
     * are for 8 bufs. Despite all this, the API must indicate whether the
     * given buffers were taken off the caller's hands, irrespective of
     * whether a release-to-hw was attempted. */
    while (num)
    {
        /* Add buffers to stockpile if they fit */
        if ((p_BmPool->spFill + num) <= p_BmPool->spMaxBufs)
        {
            memcpy(PTR_MOVE(p_BmPool->sp, sizeof(struct bm_buffer) * (p_BmPool->spFill)),
                   bufs,
                   sizeof(struct bm_buffer) * num);
            p_BmPool->spFill += num;
            num = 0; /* --> will return success no matter what */
        }
        else
        /* Do hw op if hitting the high-water threshold */
        {
            t_Error ret = BmPortalRelease(h_BmPortal,
                                          p_BmPool->bpid,
                                          (struct bm_buffer *)PTR_MOVE(p_BmPool->sp, sizeof(struct bm_buffer) * (p_BmPool->spFill - p_BmPool->spBufsCmd)),
                                          p_BmPool->spBufsCmd,
                                          flags);
            if (ret)
                return (num ? ret : E_OK);
            p_BmPool->spFill -= p_BmPool->spBufsCmd;
        }
    }

    return E_OK;
}
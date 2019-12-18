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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  h_FqidMm; int /*<<< orphan*/  h_RsrvFqidMm; } ;
typedef  TYPE_1__ t_Qm ;

/* Variables and functions */
 scalar_t__ ILLEGAL_BASE ; 
 scalar_t__ MM_Get (int /*<<< orphan*/ ,scalar_t__,scalar_t__,char*) ; 
 scalar_t__ MM_GetForce (int /*<<< orphan*/ ,scalar_t__,scalar_t__,char*) ; 
 int /*<<< orphan*/  MM_Put (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ XX_LockIntrSpinlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_UnlockIntrSpinlock (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static uint32_t ReserveFqids(t_Qm *p_Qm, uint32_t size, uint32_t alignment, bool force, uint32_t base)
{
    uint64_t    ans;
    uint32_t    intFlags;

    intFlags = XX_LockIntrSpinlock(p_Qm->lock);
    if (force)
        ans = MM_GetForce(p_Qm->h_FqidMm,
                          (uint64_t)base,
                          (uint64_t)size,
                          "QM FQID MEM");
    else
        ans = MM_Get(p_Qm->h_FqidMm,
                     (uint64_t)size,
                     alignment,
                     "QM FQID MEM");
    if (ans == ILLEGAL_BASE)
    {
        XX_UnlockIntrSpinlock(p_Qm->lock, intFlags);
        return (uint32_t)ans;
    }
    base = (uint32_t)ans;
    ans = MM_GetForce(p_Qm->h_RsrvFqidMm,
                      (uint64_t)base,
                      (uint64_t)size,
                      "QM rsrv FQID MEM");
    if (ans == ILLEGAL_BASE)
    {
        MM_Put(p_Qm->h_FqidMm, (uint64_t)base);
        XX_UnlockIntrSpinlock(p_Qm->lock, intFlags);
        return (uint32_t)ans;
    }
    XX_UnlockIntrSpinlock(p_Qm->lock, intFlags);

    return (uint32_t)base;
}
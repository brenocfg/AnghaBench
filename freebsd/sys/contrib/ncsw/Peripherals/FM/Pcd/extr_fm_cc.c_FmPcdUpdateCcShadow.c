#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_7__ {scalar_t__ ccShadowSize; scalar_t__ ccShadowAlign; void* p_CcShadow; } ;
typedef  TYPE_1__ t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  E_OK ; 
 int FALSE ; 
 void* FM_MURAM_AllocMem (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  FM_MURAM_FreeMem (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  FmPcdGetMuramHandle (TYPE_1__*) ; 
 scalar_t__ FmPcdLock (TYPE_1__*) ; 
 int /*<<< orphan*/  FmPcdUnlock (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  POWER_OF_2 (scalar_t__) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int TRUE ; 

t_Error FmPcdUpdateCcShadow(t_FmPcd *p_FmPcd, uint32_t size, uint32_t align)
{
    uint32_t intFlags;
    uint32_t newSize = 0, newAlign = 0;
    bool allocFail = FALSE;

    ASSERT_COND(p_FmPcd);

    if (!size)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("size must be larger then 0"));

    if (!POWER_OF_2(align))
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("alignment must be power of 2"));

    newSize = p_FmPcd->ccShadowSize;
    newAlign = p_FmPcd->ccShadowAlign;

    /* Check if current shadow is large enough to hold the requested size */
    if (size > p_FmPcd->ccShadowSize)
        newSize = size;

    /* Check if current shadow matches the requested alignment */
    if (align > p_FmPcd->ccShadowAlign)
        newAlign = align;

    /* If a bigger shadow size or bigger shadow alignment are required,
     a new shadow will be allocated */
    if ((newSize != p_FmPcd->ccShadowSize)
            || (newAlign != p_FmPcd->ccShadowAlign))
    {
        intFlags = FmPcdLock(p_FmPcd);

        if (p_FmPcd->p_CcShadow)
        {
            FM_MURAM_FreeMem(FmPcdGetMuramHandle(p_FmPcd), p_FmPcd->p_CcShadow);
            p_FmPcd->ccShadowSize = 0;
            p_FmPcd->ccShadowAlign = 0;
        }

        p_FmPcd->p_CcShadow = FM_MURAM_AllocMem(FmPcdGetMuramHandle(p_FmPcd),
                                                newSize, newAlign);
        if (!p_FmPcd->p_CcShadow)
        {
            allocFail = TRUE;

            /* If new shadow size allocation failed,
             re-allocate with previous parameters */
            p_FmPcd->p_CcShadow = FM_MURAM_AllocMem(
                    FmPcdGetMuramHandle(p_FmPcd), p_FmPcd->ccShadowSize,
                    p_FmPcd->ccShadowAlign);
        }

        FmPcdUnlock(p_FmPcd, intFlags);

        if (allocFail)
            RETURN_ERROR(MAJOR, E_NO_MEMORY,
                         ("MURAM allocation for CC Shadow memory"));

        p_FmPcd->ccShadowSize = newSize;
        p_FmPcd->ccShadowAlign = newAlign;
    }

    return E_OK;
}
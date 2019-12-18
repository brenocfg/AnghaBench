#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
struct TYPE_7__ {scalar_t__ h_FmPcd; int /*<<< orphan*/ * h_Spinlock; scalar_t__ p_Hmct; scalar_t__ h_NextManip; scalar_t__ owner; } ;
typedef  TYPE_1__ t_FmPcdManip ;
struct TYPE_8__ {int /*<<< orphan*/  h_FmMuram; } ;
typedef  TYPE_2__ t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FM_MURAM_FreeMem (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FmPcdManipUpdateOwner (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MANIP_IS_UNIFIED (TYPE_1__*) ; 
 scalar_t__ MANIP_IS_UNIFIED_FIRST (TYPE_1__*) ; 
 int /*<<< orphan*/  MANIP_SET_PREV (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ReleaseManipHandler (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_Free (scalar_t__) ; 
 int /*<<< orphan*/  XX_FreeSpinlock (int /*<<< orphan*/ *) ; 

t_Error FM_PCD_ManipNodeDelete(t_Handle h_ManipNode)
{
    t_FmPcdManip *p_Manip = (t_FmPcdManip *)h_ManipNode;

    SANITY_CHECK_RETURN_ERROR(p_Manip, E_INVALID_HANDLE);

    if (p_Manip->owner)
        RETURN_ERROR(
                MAJOR,
                E_INVALID_STATE,
                ("This manipulation node not be removed because this node is occupied, first - unbind this node "));

    if (p_Manip->h_NextManip)
    {
        MANIP_SET_PREV(p_Manip->h_NextManip, NULL);
        FmPcdManipUpdateOwner(p_Manip->h_NextManip, FALSE);
    }

    if (p_Manip->p_Hmct
            && (MANIP_IS_UNIFIED_FIRST(p_Manip) || !MANIP_IS_UNIFIED(p_Manip)))
        FM_MURAM_FreeMem(((t_FmPcd *)p_Manip->h_FmPcd)->h_FmMuram,
                         p_Manip->p_Hmct);

    if (p_Manip->h_Spinlock)
    {
        XX_FreeSpinlock(p_Manip->h_Spinlock);
        p_Manip->h_Spinlock = NULL;
    }

    ReleaseManipHandler(p_Manip, p_Manip->h_FmPcd);

    XX_Free(h_ManipNode);

    return E_OK;
}
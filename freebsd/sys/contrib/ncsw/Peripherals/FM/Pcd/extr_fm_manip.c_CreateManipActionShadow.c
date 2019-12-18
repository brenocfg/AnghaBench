#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_14__ {scalar_t__ dontParseAfterManip; } ;
struct TYPE_15__ {TYPE_1__ hdr; } ;
struct TYPE_16__ {TYPE_2__ u; scalar_t__ h_NextManip; } ;
typedef  TYPE_3__ t_FmPcdManipParams ;
struct TYPE_17__ {scalar_t__ tableSize; scalar_t__ dataSize; scalar_t__ dontParseAfterManip; scalar_t__* p_Data; scalar_t__* p_Hmct; struct TYPE_17__* h_PrevManip; TYPE_3__ manipParams; struct TYPE_17__* h_NextManip; scalar_t__ h_FmPcd; } ;
typedef  TYPE_4__ t_FmPcdManip ;
struct TYPE_18__ {scalar_t__* p_CcShadow; } ;
typedef  TYPE_5__ t_FmPcd ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (scalar_t__*) ; 
 int /*<<< orphan*/  BuildHmct (TYPE_4__*,TYPE_3__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ CalculateTableSize (TYPE_3__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ E_INVALID_VALUE ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetManipInfo (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ MANIP_IS_UNIFIED (TYPE_4__*) ; 
 scalar_t__ MANIP_IS_UNIFIED_NON_LAST (TYPE_4__*) ; 
 int /*<<< orphan*/  MINOR ; 
 char* NO_MSG ; 
 scalar_t__ PTR_MOVE (scalar_t__*,int) ; 
 int PTR_TO_UINT (scalar_t__*) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  e_MANIP_HMCT ; 

__attribute__((used)) static t_Error CreateManipActionShadow(t_FmPcdManip *p_Manip,
                                       t_FmPcdManipParams *p_FmPcdManipParams)
{
    uint8_t *p_WholeHmct, *p_TmpHmctPtr, newDataSize, *p_TmpDataPtr = NULL;
    uint16_t newSize;
    t_FmPcd *p_FmPcd = (t_FmPcd *)p_Manip->h_FmPcd;
    t_Error err;
    t_FmPcdManip *p_CurManip = p_Manip;

    err = CalculateTableSize(p_FmPcdManipParams, &newSize, &newDataSize);
    if (err)
        RETURN_ERROR(MINOR, err, NO_MSG);

    /* check coherency of new table parameters */
    if (newSize > p_Manip->tableSize)
        RETURN_ERROR(
                MINOR,
                E_INVALID_VALUE,
                ("New Hdr Manip configuration requires larger size than current one (command table)."));
    if (newDataSize > p_Manip->dataSize)
        RETURN_ERROR(
                MINOR,
                E_INVALID_VALUE,
                ("New Hdr Manip configuration requires larger size than current one (data)."));
    if (p_FmPcdManipParams->h_NextManip)
        RETURN_ERROR(
                MINOR, E_INVALID_VALUE,
                ("New Hdr Manip configuration can not contain h_NextManip."));
    if (MANIP_IS_UNIFIED(p_Manip) && (newSize != p_Manip->tableSize))
        RETURN_ERROR(
                MINOR,
                E_INVALID_VALUE,
                ("New Hdr Manip configuration in a chained manipulation requires different size than current one."));
    if (p_Manip->dontParseAfterManip
            != p_FmPcdManipParams->u.hdr.dontParseAfterManip)
        RETURN_ERROR(
                MINOR,
                E_INVALID_VALUE,
                ("New Hdr Manip configuration differs in dontParseAfterManip value."));

    p_Manip->tableSize = newSize;
    p_Manip->dataSize = newDataSize;

    /* Build the new table in the shadow */
    if (!MANIP_IS_UNIFIED(p_Manip))
    {
        p_TmpHmctPtr = (uint8_t*)PTR_MOVE(p_FmPcd->p_CcShadow, 16);
        if (p_Manip->p_Data)
            p_TmpDataPtr =
                    (uint8_t*)PTR_MOVE(p_TmpHmctPtr,
                            (PTR_TO_UINT(p_Manip->p_Data) - PTR_TO_UINT(p_Manip->p_Hmct)));

        BuildHmct(p_Manip, p_FmPcdManipParams, p_TmpHmctPtr, p_Manip->p_Data,
                  FALSE);
    }
    else
    {
        p_WholeHmct = (uint8_t *)GetManipInfo(p_Manip, e_MANIP_HMCT);
        ASSERT_COND(p_WholeHmct);

        /* Run till the last Manip (which is the first to configure) */
        while (MANIP_IS_UNIFIED_NON_LAST(p_CurManip))
            p_CurManip = p_CurManip->h_NextManip;

        while (p_CurManip)
        {
            /* If this is a non-head node in a unified table, point to the part of the shadow
             * which is the relative offset in HMCT.
             * else, point to the beginning of the
             * shadow table (we save 16 for the HMTD.
             */
            p_TmpHmctPtr =
                    (uint8_t*)PTR_MOVE(p_FmPcd->p_CcShadow,
                            (16 + PTR_TO_UINT(p_CurManip->p_Hmct) - PTR_TO_UINT(p_WholeHmct)));
            if (p_CurManip->p_Data)
                p_TmpDataPtr =
                        (uint8_t*)PTR_MOVE(p_FmPcd->p_CcShadow,
                                (16 + PTR_TO_UINT(p_CurManip->p_Data) - PTR_TO_UINT(p_WholeHmct)));

            BuildHmct(p_CurManip, &p_CurManip->manipParams, p_TmpHmctPtr,
                      p_TmpDataPtr, FALSE);
            p_CurManip = p_CurManip->h_PrevManip;
        }
    }

    return E_OK;
}
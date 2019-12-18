#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  inUse; int /*<<< orphan*/  scId; struct TYPE_8__* h_FmMacsec; } ;
typedef  TYPE_1__ t_SecYSc ;
typedef  TYPE_1__ t_FmMacsecSecY ;
typedef  int /*<<< orphan*/  t_Error ;
typedef  scalar_t__ e_ScType ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FmMacsecDeleteRxSc (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmMacsecDeleteTxSc (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR ; 
 int /*<<< orphan*/  NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ e_SC_RX ; 

__attribute__((used)) static t_Error FmMacsecSecYDeleteSc(t_FmMacsecSecY *p_FmMacsecSecY, t_SecYSc *p_FmSecYSc, e_ScType type)
{
    t_Error         err = E_OK;

    ASSERT_COND(p_FmMacsecSecY);
    ASSERT_COND(p_FmMacsecSecY->h_FmMacsec);
    ASSERT_COND(p_FmSecYSc);

    if (type == e_SC_RX)
    {
        if ((err = FmMacsecDeleteRxSc(p_FmMacsecSecY->h_FmMacsec, p_FmSecYSc->scId)) != E_OK)
            RETURN_ERROR(MINOR, err, NO_MSG);
    }
    else
        if ((err = FmMacsecDeleteTxSc(p_FmMacsecSecY->h_FmMacsec, p_FmSecYSc->scId)) != E_OK)
            RETURN_ERROR(MINOR, err, NO_MSG);

    p_FmSecYSc->inUse = FALSE;

    return err;
}
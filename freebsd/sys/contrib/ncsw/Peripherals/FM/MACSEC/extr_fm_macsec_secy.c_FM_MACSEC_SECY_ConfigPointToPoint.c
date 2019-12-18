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
typedef  scalar_t__ t_Handle ;
struct TYPE_3__ {int numOfRxSc; int /*<<< orphan*/  sciInsertionMode; int /*<<< orphan*/  isPointToPoint; struct TYPE_3__* p_FmMacsecSecYDriverParam; } ;
typedef  TYPE_1__ t_FmMacsecSecY ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  e_FM_MACSEC_SCI_INSERTION_MODE_IMPLICT_PTP ; 

t_Error FM_MACSEC_SECY_ConfigPointToPoint(t_Handle h_FmMacsecSecY)
{
    t_FmMacsecSecY  *p_FmMacsecSecY = (t_FmMacsecSecY *)h_FmMacsecSecY;

    SANITY_CHECK_RETURN_ERROR(p_FmMacsecSecY, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_FmMacsecSecY->p_FmMacsecSecYDriverParam, E_INVALID_STATE);

    p_FmMacsecSecY->numOfRxSc = 1;
    p_FmMacsecSecY->isPointToPoint = TRUE;
    p_FmMacsecSecY->sciInsertionMode = e_FM_MACSEC_SCI_INSERTION_MODE_IMPLICT_PTP;

    return E_OK;
}
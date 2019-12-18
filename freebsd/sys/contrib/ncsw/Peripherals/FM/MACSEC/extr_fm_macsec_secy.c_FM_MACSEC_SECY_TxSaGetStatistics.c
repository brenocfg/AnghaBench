#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * t_Handle ;
typedef  int /*<<< orphan*/  t_FmMacsecSecYTxSaStatistics ;
typedef  int /*<<< orphan*/  t_Error ;
typedef  int /*<<< orphan*/ * macsecAN_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOT_SUPPORTED ; 
 int /*<<< orphan*/  MINOR ; 
 int /*<<< orphan*/  NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 

t_Error FM_MACSEC_SECY_TxSaGetStatistics(t_Handle h_FmMacsecSecY, macsecAN_t an, t_FmMacsecSecYTxSaStatistics *p_Statistics)
{
    UNUSED(h_FmMacsecSecY);UNUSED(an);UNUSED(p_Statistics);
    RETURN_ERROR(MINOR, E_NOT_SUPPORTED, NO_MSG);
}
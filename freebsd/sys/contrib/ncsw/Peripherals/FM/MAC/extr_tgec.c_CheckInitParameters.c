#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ macId; scalar_t__ addr; TYPE_1__* p_TgecDriverParam; int /*<<< orphan*/  f_Event; int /*<<< orphan*/  f_Exception; int /*<<< orphan*/  enetMode; } ;
typedef  TYPE_2__ t_Tgec ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_4__ {int /*<<< orphan*/  no_length_check_enable; } ;

/* Variables and functions */
 scalar_t__ ENET_SPEED_FROM_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_NOT_SUPPORTED ; 
 int /*<<< orphan*/  E_OK ; 
 scalar_t__ FM_MAX_NUM_OF_10G_MACS ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MINOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ e_ENET_SPEED_10000 ; 

__attribute__((used)) static t_Error CheckInitParameters(t_Tgec    *p_Tgec)
{
    if (ENET_SPEED_FROM_MODE(p_Tgec->enetMode) < e_ENET_SPEED_10000)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Ethernet 10G MAC driver only support 10G speed"));
#if (FM_MAX_NUM_OF_10G_MACS > 0)
    if (p_Tgec->macId >= FM_MAX_NUM_OF_10G_MACS)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("macId of 10G can not be greater than 0"));
#endif /* (FM_MAX_NUM_OF_10G_MACS > 0) */

    if (p_Tgec->addr == 0)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Ethernet 10G MAC Must have a valid MAC Address"));
    if (!p_Tgec->f_Exception)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("uninitialized f_Exception"));
    if (!p_Tgec->f_Event)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("uninitialized f_Event"));
#ifdef FM_LEN_CHECK_ERRATA_FMAN_SW002
    if (!p_Tgec->p_TgecDriverParam->no_length_check_enable)
       RETURN_ERROR(MINOR, E_NOT_SUPPORTED, ("LengthCheck!"));
#endif /* FM_LEN_CHECK_ERRATA_FMAN_SW002 */
    return E_OK;
}
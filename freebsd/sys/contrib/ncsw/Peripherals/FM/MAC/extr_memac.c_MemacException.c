#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  h_App; int /*<<< orphan*/  (* f_Exception ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  p_MemMap; } ;
typedef  TYPE_1__ t_Memac ;
typedef  scalar_t__ t_Handle ;

/* Variables and functions */
 int MEMAC_ALL_ERRS_IMASK ; 
 int MEMAC_IEVNT_MGI ; 
 int /*<<< orphan*/  e_FM_MAC_EX_MAGIC_PACKET_INDICATION ; 
 int /*<<< orphan*/  fman_memac_ack_event (int /*<<< orphan*/ ,int) ; 
 int fman_memac_get_event (int /*<<< orphan*/ ,int) ; 
 int fman_memac_get_interrupt_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void MemacException(t_Handle h_Memac)
{
    t_Memac     *p_Memac = (t_Memac *)h_Memac;
    uint32_t    event, imask;

    event = fman_memac_get_event(p_Memac->p_MemMap, 0xffffffff);
    imask = fman_memac_get_interrupt_mask(p_Memac->p_MemMap);

    /* Imask include both error and notification/event bits.
       Leaving only error bits enabled by imask.
       The imask error bits are shifted by 16 bits offset from
       their corresponding location in the ievent - hence the >> 16 */
    event &= ((imask & MEMAC_ALL_ERRS_IMASK) >> 16);

    fman_memac_ack_event(p_Memac->p_MemMap, event);

    if (event & MEMAC_IEVNT_MGI)
        p_Memac->f_Exception(p_Memac->h_App, e_FM_MAC_EX_MAGIC_PACKET_INDICATION);
}
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
typedef  int /*<<< orphan*/  t_Error ;
struct dtsec_regs {struct dtsec_regs* p_MemMap; } ;
typedef  struct dtsec_regs t_Dtsec ;
typedef  int e_CommMode ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (struct dtsec_regs*) ; 
 int /*<<< orphan*/  E_OK ; 
 int e_COMM_MODE_RX ; 
 int e_COMM_MODE_TX ; 
 int /*<<< orphan*/  fman_dtsec_start_rx (struct dtsec_regs*) ; 
 int /*<<< orphan*/  fman_dtsec_start_tx (struct dtsec_regs*) ; 

__attribute__((used)) static t_Error GracefulRestart(t_Dtsec *p_Dtsec, e_CommMode mode)
{
    struct dtsec_regs *p_MemMap;

    ASSERT_COND(p_Dtsec);
    p_MemMap = p_Dtsec->p_MemMap;
    ASSERT_COND(p_MemMap);

    /* clear the graceful receive stop bit */
    if (mode & e_COMM_MODE_TX)
        fman_dtsec_start_tx(p_MemMap);

    if (mode & e_COMM_MODE_RX)
        fman_dtsec_start_rx(p_MemMap);

    return E_OK;
}
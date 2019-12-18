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

/* Variables and functions */
 int /*<<< orphan*/  FSP2_BUS_ERR ; 
 int /*<<< orphan*/  FSP2_CMU_ERR ; 
 int /*<<< orphan*/  FSP2_CONF_ERR ; 
 int /*<<< orphan*/  FSP2_MCUE ; 
 int /*<<< orphan*/  FSP2_OPBD_ERR ; 
 int /*<<< orphan*/  FSP2_RST_WRN ; 
 int /*<<< orphan*/  bus_err_handler ; 
 int /*<<< orphan*/  cmu_err_handler ; 
 int /*<<< orphan*/  conf_err_handler ; 
 int /*<<< orphan*/  mcue_handler ; 
 int /*<<< orphan*/  node_irq_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opbd_err_handler ; 
 int /*<<< orphan*/  rst_wrn_handler ; 

__attribute__((used)) static void critical_irq_setup(void)
{
	node_irq_request(FSP2_CMU_ERR, cmu_err_handler);
	node_irq_request(FSP2_BUS_ERR, bus_err_handler);
	node_irq_request(FSP2_CONF_ERR, conf_err_handler);
	node_irq_request(FSP2_OPBD_ERR, opbd_err_handler);
	node_irq_request(FSP2_MCUE, mcue_handler);
	node_irq_request(FSP2_RST_WRN, rst_wrn_handler);
}
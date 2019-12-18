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
struct synps_edac_priv {scalar_t__ baseaddr; } ;

/* Variables and functions */
 int DDR_QOSCE_MASK ; 
 int DDR_QOSUE_MASK ; 
 scalar_t__ DDR_QOS_IRQ_DB_OFST ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void disable_intr(struct synps_edac_priv *priv)
{
	/* Disable UE/CE Interrupts */
	writel(DDR_QOSUE_MASK | DDR_QOSCE_MASK,
			priv->baseaddr + DDR_QOS_IRQ_DB_OFST);
}
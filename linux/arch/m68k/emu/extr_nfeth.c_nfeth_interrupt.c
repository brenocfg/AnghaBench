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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MAX_UNIT ; 
 scalar_t__ XIF_IRQ ; 
 scalar_t__ nfEtherID ; 
 int nf_call (scalar_t__,int) ; 
 scalar_t__* nfeth_dev ; 
 int /*<<< orphan*/  recv_packet (scalar_t__) ; 

__attribute__((used)) static irqreturn_t nfeth_interrupt(int irq, void *dev_id)
{
	int i, m, mask;

	mask = nf_call(nfEtherID + XIF_IRQ, 0);
	for (i = 0, m = 1; i < MAX_UNIT; m <<= 1, i++) {
		if (mask & m && nfeth_dev[i]) {
			recv_packet(nfeth_dev[i]);
			nf_call(nfEtherID + XIF_IRQ, m);
		}
	}
	return IRQ_HANDLED;
}
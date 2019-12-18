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
struct netfront_rxq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XN_RX_LOCK (struct netfront_rxq*) ; 
 int /*<<< orphan*/  XN_RX_UNLOCK (struct netfront_rxq*) ; 
 int /*<<< orphan*/  xn_rxeof (struct netfront_rxq*) ; 

__attribute__((used)) static void
xn_rxq_intr(struct netfront_rxq *rxq)
{

	XN_RX_LOCK(rxq);
	xn_rxeof(rxq);
	XN_RX_UNLOCK(rxq);
}
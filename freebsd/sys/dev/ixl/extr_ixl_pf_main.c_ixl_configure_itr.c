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
struct ixl_pf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixl_configure_rx_itr (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_configure_tx_itr (struct ixl_pf*) ; 

void
ixl_configure_itr(struct ixl_pf *pf)
{
	ixl_configure_tx_itr(pf);
	ixl_configure_rx_itr(pf);
}
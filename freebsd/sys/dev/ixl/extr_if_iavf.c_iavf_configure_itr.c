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
struct iavf_sc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iavf_configure_rx_itr (struct iavf_sc*) ; 
 int /*<<< orphan*/  iavf_configure_tx_itr (struct iavf_sc*) ; 

__attribute__((used)) static void
iavf_configure_itr(struct iavf_sc *sc)
{
	iavf_configure_tx_itr(sc);
	iavf_configure_rx_itr(sc);
}
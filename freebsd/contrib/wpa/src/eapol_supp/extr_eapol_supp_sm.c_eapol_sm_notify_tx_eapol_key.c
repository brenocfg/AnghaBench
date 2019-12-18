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
struct eapol_sm {int /*<<< orphan*/  dot1xSuppEapolFramesTx; } ;

/* Variables and functions */

void eapol_sm_notify_tx_eapol_key(struct eapol_sm *sm)
{
	if (sm)
		sm->dot1xSuppEapolFramesTx++;
}
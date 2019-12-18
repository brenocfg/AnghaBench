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
struct ieee802_1x_cp_sm {scalar_t__ transmit_when; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee802_1x_cp_step_run (struct ieee802_1x_cp_sm*) ; 

__attribute__((used)) static void
ieee802_1x_cp_transmit_when_timeout(void *eloop_ctx, void *timeout_ctx)
{
	struct ieee802_1x_cp_sm *sm = eloop_ctx;
	sm->transmit_when = 0;
	ieee802_1x_cp_step_run(sm);
}
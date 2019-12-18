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
typedef  int /*<<< orphan*/  VCHIQ_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  g_state ; 
 int /*<<< orphan*/  remote_event_pollall (int /*<<< orphan*/ *) ; 
 unsigned int vchiq_read_4 (int) ; 

__attribute__((used)) static void
bcm_vchiq_intr(void *arg)
{
	VCHIQ_STATE_T *state = &g_state;
	unsigned int status;

	/* Read (and clear) the doorbell */
	status = vchiq_read_4(0x40);

	if (status & 0x4) {  /* Was the doorbell rung? */
		remote_event_pollall(state);
	}
}
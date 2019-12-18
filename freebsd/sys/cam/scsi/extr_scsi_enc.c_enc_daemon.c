#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intr_config_hook {int /*<<< orphan*/ * ich_func; } ;
struct TYPE_4__ {int enc_flags; scalar_t__ pending_actions; int /*<<< orphan*/  periph; int /*<<< orphan*/ * enc_daemon; int /*<<< orphan*/  status_updater; struct intr_config_hook enc_boot_hold_ch; int /*<<< orphan*/  current_action; } ;
typedef  TYPE_1__ enc_softc_t ;

/* Variables and functions */
 int ENC_FLAG_SHUTDOWN ; 
 int /*<<< orphan*/  ENC_UPDATE_NONE ; 
 int /*<<< orphan*/  PUSER ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  cam_periph_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_sleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_intrhook_disestablish (struct intr_config_hook*) ; 
 int /*<<< orphan*/  enc_fsm_step (TYPE_1__*) ; 
 int /*<<< orphan*/  enc_status_updater ; 
 int hz ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
enc_daemon(void *arg)
{
	enc_softc_t *enc;

	enc = arg;

	cam_periph_lock(enc->periph);
	while ((enc->enc_flags & ENC_FLAG_SHUTDOWN) == 0) {
		if (enc->pending_actions == 0) {
			struct intr_config_hook *hook;

			/*
			 * Reset callout and msleep, or
			 * issue timed task completion
			 * status command.
			 */
			enc->current_action = ENC_UPDATE_NONE;

			/*
			 * We've been through our state machine at least
			 * once.  Allow the transition to userland.
			 */
			hook = &enc->enc_boot_hold_ch;
			if (hook->ich_func != NULL) {
				config_intrhook_disestablish(hook);
				hook->ich_func = NULL;
			}

			callout_reset(&enc->status_updater, 60*hz,
				      enc_status_updater, enc);

			cam_periph_sleep(enc->periph, enc->enc_daemon,
					 PUSER, "idle", 0);
		} else {
			enc_fsm_step(enc);
		}
	}
	enc->enc_daemon = NULL;
	cam_periph_unlock(enc->periph);
	cam_periph_release(enc->periph);
	kproc_exit(0);
}
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
struct i2s_softc {int dummy; } ;

/* Variables and functions */
 size_t AUDIO_HW_RESET ; 
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  RESET_HOLD_TIME ; 
 int /*<<< orphan*/  RESET_RELEASE_TIME ; 
 int /*<<< orphan*/  RESET_SETUP_TIME ; 
 scalar_t__* gpio_ctrls ; 
 int /*<<< orphan*/  gpio_write (size_t,int) ; 
 int reset_active ; 

__attribute__((used)) static void
i2s_audio_hw_reset(struct i2s_softc *sc)
{
	if (gpio_ctrls[AUDIO_HW_RESET]) {
		DPRINTF(("resetting codec\n"));

		gpio_write(AUDIO_HW_RESET, !reset_active);   /* Negate RESET */
		DELAY(RESET_SETUP_TIME);

		gpio_write(AUDIO_HW_RESET, reset_active);    /* Assert RESET */
		DELAY(RESET_HOLD_TIME);

		gpio_write(AUDIO_HW_RESET, !reset_active);   /* Negate RESET */
		DELAY(RESET_RELEASE_TIME);
	
	} else {
		DPRINTF(("no audio_hw_reset\n"));
	}
}
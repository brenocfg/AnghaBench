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

/* Variables and functions */
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  MIDIMKMINOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIDI_DEV_MIDICTL ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  midi_devs ; 
 int /*<<< orphan*/  midistat_cdevsw ; 
 int /*<<< orphan*/  midistat_dev ; 
 int /*<<< orphan*/  midistat_lock ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
midi_load(void)
{
	sx_init(&midistat_lock, "midistat lock");
	TAILQ_INIT(&midi_devs);

	midistat_dev = make_dev(&midistat_cdevsw,
	    MIDIMKMINOR(0, MIDI_DEV_MIDICTL, 0),
	    UID_ROOT, GID_WHEEL, 0666, "midistat");

	return 0;
}
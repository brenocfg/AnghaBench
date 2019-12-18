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
typedef  int /*<<< orphan*/  uint32_t ;
struct uinput_cdev_state {int /*<<< orphan*/  ucs_state; int /*<<< orphan*/  ucs_evdev; } ;
struct input_id {int /*<<< orphan*/  version; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bustype; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UINPUT_CONFIGURED ; 
 int /*<<< orphan*/  evdev_set_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_set_name (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
uinput_setup_dev(struct uinput_cdev_state *state, struct input_id *id,
    char *name, uint32_t ff_effects_max)
{

	if (name[0] == 0)
		return (EINVAL);

	evdev_set_name(state->ucs_evdev, name);
	evdev_set_id(state->ucs_evdev, id->bustype, id->vendor, id->product,
	    id->version);
	state->ucs_state = UINPUT_CONFIGURED;

	return (0);
}
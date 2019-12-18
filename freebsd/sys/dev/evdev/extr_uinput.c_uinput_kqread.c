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
struct uinput_cdev_state {int dummy; } ;
struct knote {scalar_t__ kn_hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  UINPUT_EMPTYQ (struct uinput_cdev_state*) ; 
 int /*<<< orphan*/  UINPUT_LOCK_ASSERT (struct uinput_cdev_state*) ; 

__attribute__((used)) static int
uinput_kqread(struct knote *kn, long hint)
{
	struct uinput_cdev_state *state;
	int ret;

	state = (struct uinput_cdev_state *)kn->kn_hook;

	UINPUT_LOCK_ASSERT(state);

	ret = !UINPUT_EMPTYQ(state);
	return (ret);
}
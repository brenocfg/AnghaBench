#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct uinput_cdev_state {int /*<<< orphan*/  ucs_lock; TYPE_1__ ucs_selp; int /*<<< orphan*/  ucs_evdev; } ;
struct thread {int dummy; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_EVDEV ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  devfs_set_cdevpriv (struct uinput_cdev_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_alloc () ; 
 int /*<<< orphan*/  knlist_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct uinput_cdev_state* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  uinput_dtor ; 
 int /*<<< orphan*/  uinput_knl_assert_locked ; 
 int /*<<< orphan*/  uinput_knl_assert_unlocked ; 
 int /*<<< orphan*/  uinput_knllock ; 
 int /*<<< orphan*/  uinput_knlunlock ; 

__attribute__((used)) static int
uinput_open(struct cdev *dev, int oflags, int devtype, struct thread *td)
{
	struct uinput_cdev_state *state;

	state = malloc(sizeof(struct uinput_cdev_state), M_EVDEV,
	    M_WAITOK | M_ZERO);
	state->ucs_evdev = evdev_alloc();

	sx_init(&state->ucs_lock, "uinput");
	knlist_init(&state->ucs_selp.si_note, &state->ucs_lock, uinput_knllock,
	    uinput_knlunlock, uinput_knl_assert_locked,
	    uinput_knl_assert_unlocked);

	devfs_set_cdevpriv(state, uinput_dtor);
	return (0);
}
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
struct thread {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * key; } ;
typedef  TYPE_1__ keymap_t ;

/* Variables and functions */
 int NUM_KEYS ; 
 int key_change_ok (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct thread*) ; 

__attribute__((used)) static int
keymap_change_ok(keymap_t *oldmap, keymap_t *newmap, struct thread *td)
{
	int keycode, error;

	for (keycode = 0; keycode < NUM_KEYS; keycode++) {
		if ((error = key_change_ok(&oldmap->key[keycode],
		    &newmap->key[keycode], td)) != 0)
			return (error);
	}
	return (0);
}
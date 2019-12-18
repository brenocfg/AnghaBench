#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
typedef  TYPE_1__* bthid_session_p ;
typedef  int /*<<< orphan*/  bitstr_t ;
struct TYPE_3__ {int /*<<< orphan*/ * keys1; int /*<<< orphan*/  ukbd; int /*<<< orphan*/  vkbd; int /*<<< orphan*/ * keys2; int /*<<< orphan*/ * srv; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bit_clear (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bit_ffs (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  bit_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bit_test (int /*<<< orphan*/ *,int) ; 
 int bitstr_size (int) ; 
 int /*<<< orphan*/  kbd_write (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uinput_kbd_write (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int xsize ; 

int32_t
kbd_process_keys(bthid_session_p s)
{
	bitstr_t	diff[bitstr_size(xsize)];
	int32_t		f1, f2, i;

	assert(s != NULL);
	assert(s->srv != NULL);

	/* Check if the new keys have been pressed */
	bit_ffs(s->keys1, xsize, &f1);

	/* Check if old keys still pressed */
	bit_ffs(s->keys2, xsize, &f2);

	if (f1 == -1) {
		/* no new key pressed */
		if (f2 != -1) {
			/* release old keys */
			kbd_write(s->keys2, f2, 0, s->vkbd);
			uinput_kbd_write(s->keys2, f2, 0, s->ukbd);
			memset(s->keys2, 0, bitstr_size(xsize));
		}

		return (0);
	}

	if (f2 == -1) {
		/* no old keys, but new keys pressed */
		assert(f1 != -1);
		
		memcpy(s->keys2, s->keys1, bitstr_size(xsize));
		kbd_write(s->keys1, f1, 1, s->vkbd);
		uinput_kbd_write(s->keys1, f1, 1, s->ukbd);
		memset(s->keys1, 0, bitstr_size(xsize));

		return (0);
	}

	/* new keys got pressed, old keys got released */
	memset(diff, 0, bitstr_size(xsize));

	for (i = f2; i < xsize; i ++) {
		if (bit_test(s->keys2, i)) {
			if (!bit_test(s->keys1, i)) {
				bit_clear(s->keys2, i);
				bit_set(diff, i);
			}
		}
	}

	for (i = f1; i < xsize; i++) {
		if (bit_test(s->keys1, i)) {
			if (!bit_test(s->keys2, i))
				bit_set(s->keys2, i);
			else
				bit_clear(s->keys1, i);
		}
	}

	bit_ffs(diff, xsize, &f2);
	if (f2 > 0) {
		kbd_write(diff, f2, 0, s->vkbd);
		uinput_kbd_write(diff, f2, 0, s->ukbd);
	}

	bit_ffs(s->keys1, xsize, &f1);
	if (f1 > 0) {
		kbd_write(s->keys1, f1, 1, s->vkbd);
		uinput_kbd_write(s->keys1, f1, 1, s->ukbd);
		memset(s->keys1, 0, bitstr_size(xsize));
	}

	return (0);
}
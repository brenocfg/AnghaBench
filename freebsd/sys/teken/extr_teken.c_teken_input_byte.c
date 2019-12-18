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
struct TYPE_4__ {int t_stateflags; int t_utf8_left; unsigned char t_utf8_partial; } ;
typedef  TYPE_1__ teken_t ;

/* Variables and functions */
 int TS_8BIT ; 
 int /*<<< orphan*/  teken_input_char (TYPE_1__*,unsigned char) ; 
 int /*<<< orphan*/  teken_printf (char*,int) ; 

__attribute__((used)) static void
teken_input_byte(teken_t *t, unsigned char c)
{

	/*
	 * UTF-8 handling.
	 */
	if ((c & 0x80) == 0x00 || t->t_stateflags & TS_8BIT) {
		/* One-byte sequence. */
		t->t_utf8_left = 0;
		teken_input_char(t, c);
	} else if ((c & 0xe0) == 0xc0) {
		/* Two-byte sequence. */
		t->t_utf8_left = 1;
		t->t_utf8_partial = c & 0x1f;
	} else if ((c & 0xf0) == 0xe0) {
		/* Three-byte sequence. */
		t->t_utf8_left = 2;
		t->t_utf8_partial = c & 0x0f;
	} else if ((c & 0xf8) == 0xf0) {
		/* Four-byte sequence. */
		t->t_utf8_left = 3;
		t->t_utf8_partial = c & 0x07;
	} else if ((c & 0xc0) == 0x80) {
		if (t->t_utf8_left == 0)
			return;
		t->t_utf8_left--;
		t->t_utf8_partial = (t->t_utf8_partial << 6) | (c & 0x3f);
		if (t->t_utf8_left == 0) {
			teken_printf("Got UTF-8 char %x\n", t->t_utf8_partial);
			teken_input_char(t, t->t_utf8_partial);
		}
	}
}
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
#define  KDB_ALT_BREAK_SEEN_CR 130 
#define  KDB_ALT_BREAK_SEEN_CR_TILDE 129 
#define  KDB_ALT_BREAK_SEEN_NONE 128 
 int KDB_REQ_DEBUGGER ; 
 int KDB_REQ_PANIC ; 
 int KDB_REQ_REBOOT ; 
 int KEY_CR ; 
 int KEY_CRTLB ; 
 int KEY_CRTLP ; 
 int KEY_CRTLR ; 
 int KEY_TILDE ; 

__attribute__((used)) static int
kdb_alt_break_state(int key, int *state)
{
	int brk;

	/* All states transition to KDB_ALT_BREAK_SEEN_CR on a CR. */
	if (key == KEY_CR) {
		*state = KDB_ALT_BREAK_SEEN_CR;
		return (0);
	}

	brk = 0;
	switch (*state) {
	case KDB_ALT_BREAK_SEEN_CR:
		*state = KDB_ALT_BREAK_SEEN_NONE;
		if (key == KEY_TILDE)
			*state = KDB_ALT_BREAK_SEEN_CR_TILDE;
		break;
	case KDB_ALT_BREAK_SEEN_CR_TILDE:
		*state = KDB_ALT_BREAK_SEEN_NONE;
		if (key == KEY_CRTLB)
			brk = KDB_REQ_DEBUGGER;
		else if (key == KEY_CRTLP)
			brk = KDB_REQ_PANIC;
		else if (key == KEY_CRTLR)
			brk = KDB_REQ_REBOOT;
		break;
	case KDB_ALT_BREAK_SEEN_NONE:
	default:
		*state = KDB_ALT_BREAK_SEEN_NONE;
		break;
	}
	return (brk);
}
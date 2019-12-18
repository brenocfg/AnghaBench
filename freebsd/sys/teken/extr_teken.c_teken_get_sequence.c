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
struct TYPE_3__ {int t_stateflags; } ;
typedef  TYPE_1__ teken_t ;

/* Variables and functions */
 int TS_CONS25 ; 
 int TS_CONS25KEYS ; 
 int TS_CURSORKEYS ; 
 char const** special_strings_ckeys ; 
 char const** special_strings_cons25 ; 
 char const** special_strings_normal ; 

const char *
teken_get_sequence(const teken_t *t, unsigned int k)
{

	/* Cons25 mode. */
	if ((t->t_stateflags & (TS_CONS25 | TS_CONS25KEYS)) ==
	    (TS_CONS25 | TS_CONS25KEYS))
		return (NULL);	/* Don't override good kbd(4) strings. */
	if (t->t_stateflags & TS_CONS25 &&
	    k < sizeof special_strings_cons25 / sizeof(char *))
		return (special_strings_cons25[k]);

	/* Cursor keys mode. */
	if (t->t_stateflags & TS_CURSORKEYS &&
	    k < sizeof special_strings_ckeys / sizeof(char *))
		return (special_strings_ckeys[k]);

	/* Default xterm sequences. */
	if (k < sizeof special_strings_normal / sizeof(char *))
		return (special_strings_normal[k]);

	return (NULL);
}
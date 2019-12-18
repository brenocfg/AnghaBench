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
typedef  int /*<<< orphan*/  keyboard_t ;
typedef  int /*<<< orphan*/  keyboard_switch_t ;

/* Variables and functions */
 scalar_t__ ARRAY_DELTA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** kbdsw ; 
 int /*<<< orphan*/ ** keyboard ; 
 int keyboards ; 
 int /*<<< orphan*/ ** malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int rounddown (scalar_t__,scalar_t__) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static int
kbd_realloc_array(void)
{
	keyboard_t **new_kbd;
	keyboard_switch_t **new_kbdsw;
	int newsize;
	int s;

	s = spltty();
	newsize = rounddown(keyboards + ARRAY_DELTA, ARRAY_DELTA);
	new_kbd = malloc(sizeof(*new_kbd)*newsize, M_DEVBUF, M_NOWAIT|M_ZERO);
	if (new_kbd == NULL) {
		splx(s);
		return (ENOMEM);
	}
	new_kbdsw = malloc(sizeof(*new_kbdsw)*newsize, M_DEVBUF,
			    M_NOWAIT|M_ZERO);
	if (new_kbdsw == NULL) {
		free(new_kbd, M_DEVBUF);
		splx(s);
		return (ENOMEM);
	}
	bcopy(keyboard, new_kbd, sizeof(*keyboard)*keyboards);
	bcopy(kbdsw, new_kbdsw, sizeof(*kbdsw)*keyboards);
	if (keyboards > 1) {
		free(keyboard, M_DEVBUF);
		free(kbdsw, M_DEVBUF);
	}
	keyboard = new_kbd;
	kbdsw = new_kbdsw;
	keyboards = newsize;
	splx(s);

	if (bootverbose)
		printf("kbd: new array size %d\n", keyboards);

	return (0);
}
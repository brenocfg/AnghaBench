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
typedef  int /*<<< orphan*/  keybuf ;

/* Variables and functions */
 int /*<<< orphan*/  isgraph (char) ; 
 int pcg32_random () ; 

__attribute__((used)) static const char *
random_key (size_t *lenptr)
{
	static char keybuf[512];
	int keylen, i;
	char c;

	keylen = pcg32_random () % (sizeof (keybuf) - 1) + 1;

	for (i = 0; i < keylen; i ++) {
		do {
			c = pcg32_random () & 0xFF;
		} while (!isgraph (c));

		keybuf[i] = c;
	}

	*lenptr = keylen;
	return keybuf;
}
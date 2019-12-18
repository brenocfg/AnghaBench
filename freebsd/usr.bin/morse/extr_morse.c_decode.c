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
struct morsetab {char inchar; int /*<<< orphan*/  morse; } ;

/* Variables and functions */
 struct morsetab* hightab ; 
 struct morsetab* mtab ; 
 int /*<<< orphan*/  putchar (char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

void
decode(char *p)
{
	char c;
	const struct morsetab *m;

	c = ' ';
	for (m = mtab; m != NULL && m->inchar != '\0'; m++) {
		if (strcmp(m->morse, p) == 0) {
			c = m->inchar;
			break;
		}
	}

	if (c == ' ')
		for (m = hightab; m != NULL && m->inchar != '\0'; m++) {
			if (strcmp(m->morse, p) == 0) {
				c = m->inchar;
				break;
			}
		}

	putchar(c);
}
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
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 char* strdup (char*) ; 

void
interp_emit_prompt(void)
{
	char		*pr, *p, *cp, *ev;

	if ((cp = getenv("prompt")) == NULL)
		cp = ">";
	pr = p = strdup(cp);

	while (*p != 0) {
		if ((*p == '$') && (*(p+1) == '{')) {
			for (cp = p + 2; (*cp != 0) && (*cp != '}'); cp++)
				;
			*cp = 0;
			ev = getenv(p + 2);

			if (ev != NULL)
				printf("%s", ev);
			p = cp + 1;
			continue;
		}
		putchar(*p++);
	}
	putchar(' ');
	free(pr);
}
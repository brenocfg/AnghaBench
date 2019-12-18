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
 char* editedhost ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

void
edithost(char *pat, char *host)
{
	char *res = editedhost;

	if (pat) {
		while (*pat) {
			switch (*pat) {

			case '#':
				if (*host)
					host++;
				break;

			case '@':
				if (*host)
					*res++ = *host++;
				break;

			default:
				*res++ = *pat;
				break;
			}
			if (res == &editedhost[sizeof editedhost - 1]) {
				*res = '\0';
				return;
			}
			pat++;
		}
	}
	if (*host)
		(void) strncpy(res, host,
				sizeof editedhost - (res - editedhost) -1);
	else
		*res = '\0';
	editedhost[sizeof editedhost - 1] = '\0';
}
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
typedef  size_t u_int ;

/* Variables and functions */
 size_t strlen (char const*) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static char *
complete_ambiguous(const char *word, char **list, size_t count)
{
	if (word == NULL)
		return NULL;

	if (count > 0) {
		u_int y, matchlen = strlen(list[0]);

		/* Find length of common stem */
		for (y = 1; list[y]; y++) {
			u_int x;

			for (x = 0; x < matchlen; x++)
				if (list[0][x] != list[y][x])
					break;

			matchlen = x;
		}

		if (matchlen > strlen(word)) {
			char *tmp = xstrdup(list[0]);

			tmp[matchlen] = '\0';
			return tmp;
		}
	}

	return xstrdup(word);
}
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
typedef  int /*<<< orphan*/  hex ;

/* Variables and functions */
 char* calloc (int,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ strtoumax (char*,int /*<<< orphan*/ *,int) ; 

char *
parseval(char *p, size_t len)
{
	char	 hex[3];
	char	*buffer;
	size_t	 i, j;

	if ((buffer = calloc(1, len + 1)) == NULL)
		return NULL;

	for (i = j = 0; j < len; i++) {
		if (p[j] == '\\') {
			strlcpy(hex, p + j + 1, sizeof(hex));
			buffer[i] = (char)strtoumax(hex, NULL, 16);
			j += 3;
		} else {
			buffer[i] = p[j];
			j++;
		}
	}

	return buffer;
}
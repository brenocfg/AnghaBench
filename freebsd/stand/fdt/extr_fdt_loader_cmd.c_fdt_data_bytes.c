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
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static int
fdt_data_bytes(const void *data, int len, char **buf)
{
	char *b, *tmp;
	const char *d;
	int i, l;

	/*
	 * Calculate the length for the string and allocate memory.
	 */

	/* Each byte translates to 2 output characters */
	l = len * 2;
	if (len > 1)
		/* Each consecutive byte requires a " " separator. */
		l += (len - 1) * 1;
	/* Each byte will have a "0x" prefix */
	l += len * 2;
	/* Space for surrounding [] and terminator. */
	l += 3;

	b = (char *)malloc(l);
	tmp = (char *)malloc(l);
	if (b == NULL)
		goto error;

	if (tmp == NULL) {
		free(b);
		goto error;
	}

	b[0] = '\0';
	strcat(b, "[");

	for (i = 0, d = data; i < len; i++) {
		sprintf(tmp, "0x%02x%s", d[i], i < len - 1 ? " " : "");
		strcat(b, tmp);
	}
	strcat(b, "]");
	*buf = b;

	free(tmp);

	return (0);
error:
	return (1);
}
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
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
fdt_data_str(const void *data, int len, int count, char **buf)
{
	char *b, *tmp;
	const char *d;
	int buf_len, i, l;

	/*
	 * Calculate the length for the string and allocate memory.
	 *
	 * Note that 'len' already includes at least one terminator.
	 */
	buf_len = len;
	if (count > 1) {
		/*
		 * Each token had already a terminator buried in 'len', but we
		 * only need one eventually, don't count space for these.
		 */
		buf_len -= count - 1;

		/* Each consecutive token requires a ", " separator. */
		buf_len += count * 2;
	}

	/* Add some space for surrounding double quotes. */
	buf_len += count * 2;

	/* Note that string being put in 'tmp' may be as big as 'buf_len'. */
	b = (char *)malloc(buf_len);
	tmp = (char *)malloc(buf_len);
	if (b == NULL)
		goto error;

	if (tmp == NULL) {
		free(b);
		goto error;
	}

	b[0] = '\0';

	/*
	 * Now that we have space, format the string.
	 */
	i = 0;
	do {
		d = (const char *)data + i;
		l = strlen(d) + 1;

		sprintf(tmp, "\"%s\"%s", d,
		    (i + l) < len ?  ", " : "");
		strcat(b, tmp);

		i += l;

	} while (i < len);
	*buf = b;

	free(tmp);

	return (0);
error:
	return (1);
}
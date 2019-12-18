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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int fdt32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static int
fdt_data_cell(const void *data, int len, char **buf)
{
	char *b, *tmp;
	const uint32_t *c;
	int count, i, l;

	/* Number of cells */
	count = len / 4;

	/*
	 * Calculate the length for the string and allocate memory.
	 */

	/* Each byte translates to 2 output characters */
	l = len * 2;
	if (count > 1) {
		/* Each consecutive cell requires a " " separator. */
		l += (count - 1) * 1;
	}
	/* Each cell will have a "0x" prefix */
	l += count * 2;
	/* Space for surrounding <> and terminator */
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
	strcat(b, "<");

	for (i = 0; i < len; i += 4) {
		c = (const uint32_t *)((const uint8_t *)data + i);
		sprintf(tmp, "0x%08x%s", fdt32_to_cpu(*c),
		    i < (len - 4) ? " " : "");
		strcat(b, tmp);
	}
	strcat(b, ">");
	*buf = b;

	free(tmp);

	return (0);
error:
	return (1);
}
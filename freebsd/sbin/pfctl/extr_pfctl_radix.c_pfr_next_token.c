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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUF_SIZE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 char fgetc (int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (char) ; 

int
pfr_next_token(char buf[BUF_SIZE], FILE *fp)
{
	static char	next_ch = ' ';
	int		i = 0;

	for (;;) {
		/* skip spaces */
		while (isspace(next_ch) && !feof(fp))
			next_ch = fgetc(fp);
		/* remove from '#' until end of line */
		if (next_ch == '#')
			while (!feof(fp)) {
				next_ch = fgetc(fp);
				if (next_ch == '\n')
					break;
			}
		else
			break;
	}
	if (feof(fp)) {
		next_ch = ' ';
		return (0);
	}
	do {
		if (i < BUF_SIZE)
			buf[i++] = next_ch;
		next_ch = fgetc(fp);
	} while (!feof(fp) && !isspace(next_ch));
	if (i >= BUF_SIZE) {
		errno = EINVAL;
		return (-1);
	}
	buf[i] = '\0';
	return (1);
}
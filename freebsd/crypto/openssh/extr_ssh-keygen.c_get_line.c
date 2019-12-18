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
 int EOF ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int ungetc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_line(FILE *fp, char *line, size_t len)
{
	int c;
	size_t pos = 0;

	line[0] = '\0';
	while ((c = fgetc(fp)) != EOF) {
		if (pos >= len - 1)
			fatal("input line too long.");
		switch (c) {
		case '\r':
			c = fgetc(fp);
			if (c != EOF && c != '\n' && ungetc(c, fp) == EOF)
				fatal("unget: %s", strerror(errno));
			return pos;
		case '\n':
			return pos;
		}
		line[pos++] = c;
		line[pos] = '\0';
	}
	/* We reached EOF */
	return -1;
}
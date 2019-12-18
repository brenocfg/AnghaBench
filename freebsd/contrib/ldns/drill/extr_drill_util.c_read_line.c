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
 int getc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
read_line(FILE *input, char *line, size_t len)
{
	int i;
	int c;

	for (i = 0; i < (int)len-1; i++) {
		c = getc(input);
		if (c == EOF) {
			return -1;
		} else if (c != '\n') {
			line[i] = c;
		} else {
			break;
		}
	}
	line[i] = '\0';
	return i;
}
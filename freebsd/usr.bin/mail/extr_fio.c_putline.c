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
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 

int
putline(FILE *obuf, char *linebuf, int outlf)
{
	int c;

	c = strlen(linebuf);
	(void)fwrite(linebuf, sizeof(*linebuf), c, obuf);
	if (outlf) {
		fprintf(obuf, "\n");
		c++;
	}
	if (ferror(obuf))
		return (-1);
	return (c);
}
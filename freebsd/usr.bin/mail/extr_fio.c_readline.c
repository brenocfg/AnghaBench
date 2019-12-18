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
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 

int
readline(FILE *ibuf, char *linebuf, int linesize)
{
	int n;

	clearerr(ibuf);
	if (fgets(linebuf, linesize, ibuf) == NULL)
		return (-1);
	n = strlen(linebuf);
	if (n > 0 && linebuf[n - 1] == '\n')
		linebuf[--n] = '\0';
	if (n > 0 && linebuf[n - 1] == '\r')
		linebuf[--n] = '\0';
	return (n);
}
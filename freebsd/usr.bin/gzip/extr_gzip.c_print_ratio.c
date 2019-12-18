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
typedef  int u_int ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
print_ratio(off_t in, off_t out, FILE *where)
{
	int percent10;	/* 10 * percent */
	off_t diff;
	char buff[8];
	int len;

	diff = in - out/2;
	if (in == 0 && out == 0)
		percent10 = 0;
	else if (diff < 0)
		/*
		 * Output is more than double size of input! print -99.9%
		 * Quite possibly we've failed to get the original size.
		 */
		percent10 = -999;
	else {
		/*
		 * We only need 12 bits of result from the final division,
		 * so reduce the values until a 32bit division will suffice.
		 */
		while (in > 0x100000) {
			diff >>= 1;
			in >>= 1;
		}
		if (in != 0)
			percent10 = ((u_int)diff * 2000) / (u_int)in - 1000;
		else
			percent10 = 0;
	}

	len = snprintf(buff, sizeof buff, "%2.2d.", percent10);
	/* Move the '.' to before the last digit */
	buff[len - 1] = buff[len - 2];
	buff[len - 2] = '.';
	fprintf(where, "%5s%%", buff);
}
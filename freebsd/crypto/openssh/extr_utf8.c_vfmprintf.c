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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int vasnmprintf (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

int
vfmprintf(FILE *stream, const char *fmt, va_list ap)
{
	char	*str;
	int	 ret;

	if ((ret = vasnmprintf(&str, INT_MAX, NULL, fmt, ap)) < 0)
		return -1;
	if (fputs(str, stream) == EOF)
		ret = -1;
	free(str);
	return ret;
}
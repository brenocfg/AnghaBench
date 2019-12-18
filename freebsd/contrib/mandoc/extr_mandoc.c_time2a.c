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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_mday; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 char* mandoc_malloc (int) ; 
 char* mandoc_strdup (char*) ; 
 int snprintf (char*,int,char*,int) ; 
 size_t strftime (char*,int,char*,struct tm*) ; 

__attribute__((used)) static char *
time2a(time_t t)
{
	struct tm	*tm;
	char		*buf, *p;
	size_t		 ssz;
	int		 isz;

	buf = NULL;
	tm = localtime(&t);
	if (tm == NULL)
		goto fail;

	/*
	 * Reserve space:
	 * up to 9 characters for the month (September) + blank
	 * up to 2 characters for the day + comma + blank
	 * 4 characters for the year and a terminating '\0'
	 */

	p = buf = mandoc_malloc(10 + 4 + 4 + 1);

	if ((ssz = strftime(p, 10 + 1, "%B ", tm)) == 0)
		goto fail;
	p += (int)ssz;

	/*
	 * The output format is just "%d" here, not "%2d" or "%02d".
	 * That's also the reason why we can't just format the
	 * date as a whole with "%B %e, %Y" or "%B %d, %Y".
	 * Besides, the present approach is less prone to buffer
	 * overflows, in case anybody should ever introduce the bug
	 * of looking at LC_TIME.
	 */

	isz = snprintf(p, 4 + 1, "%d, ", tm->tm_mday);
	if (isz < 0 || isz > 4)
		goto fail;
	p += isz;

	if (strftime(p, 4 + 1, "%Y", tm) == 0)
		goto fail;
	return buf;

fail:
	free(buf);
	return mandoc_strdup("");
}
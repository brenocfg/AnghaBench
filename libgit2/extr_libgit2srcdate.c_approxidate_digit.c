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
struct tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  isdigit (char) ; 
 size_t match_multi_number (unsigned long,char,char const*,char*,struct tm*) ; 
 unsigned long strtoul (char const*,char**,int) ; 

__attribute__((used)) static const char *approxidate_digit(const char *date, struct tm *tm, int *num)
{
	char *end;
	unsigned long number = strtoul(date, &end, 10);

	switch (*end) {
	case ':':
	case '.':
	case '/':
	case '-':
		if (isdigit(end[1])) {
			size_t match = match_multi_number(number, *end, date, end, tm);
			if (match)
				return date + match;
		}
	}

	/* Accept zero-padding only for small numbers ("Dec 02", never "Dec 0002") */
	if (date[0] != '0' || end - date <= 2)
		*num = number;
	return end;
}
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
typedef  int timestamp_t ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  isdigit (char) ; 
 int match_multi_number (int,char,char const*,char*,struct tm*,int /*<<< orphan*/ ) ; 
 int parse_timestamp (char const*,char**,int) ; 

__attribute__((used)) static const char *approxidate_digit(const char *date, struct tm *tm, int *num,
				     time_t now)
{
	char *end;
	timestamp_t number = parse_timestamp(date, &end, 10);

	switch (*end) {
	case ':':
	case '.':
	case '/':
	case '-':
		if (isdigit(end[1])) {
			int match = match_multi_number(number, *end, date, end,
						       tm, now);
			if (match)
				return date + match;
		}
	}

	/* Accept zero-padding only for small numbers ("Dec 02", never "Dec 0002") */
	if (date[0] != '0' || end - date <= 2)
		*num = number;
	return end;
}
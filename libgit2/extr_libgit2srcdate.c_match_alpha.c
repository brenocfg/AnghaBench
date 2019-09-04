#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tm {unsigned int tm_mon; unsigned int tm_wday; int tm_hour; } ;
struct TYPE_3__ {char* name; int offset; scalar_t__ dst; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int match_string (char const*,char*) ; 
 char** month_names ; 
 size_t skip_alpha (char const*) ; 
 size_t strlen (char*) ; 
 TYPE_1__* timezone_names ; 
 char** weekday_names ; 

__attribute__((used)) static size_t match_alpha(const char *date, struct tm *tm, int *offset)
{
	unsigned int i;

	for (i = 0; i < 12; i++) {
		size_t match = match_string(date, month_names[i]);
		if (match >= 3) {
			tm->tm_mon = i;
			return match;
		}
	}

	for (i = 0; i < 7; i++) {
		size_t match = match_string(date, weekday_names[i]);
		if (match >= 3) {
			tm->tm_wday = i;
			return match;
		}
	}

	for (i = 0; i < ARRAY_SIZE(timezone_names); i++) {
		size_t match = match_string(date, timezone_names[i].name);
		if (match >= 3 || match == strlen(timezone_names[i].name)) {
			int off = timezone_names[i].offset;

			/* This is bogus, but we like summer */
			off += timezone_names[i].dst;

			/* Only use the tz name offset if we don't have anything better */
			if (*offset == -1)
				*offset = 60*off;

			return match;
		}
	}

	if (match_string(date, "PM") == 2) {
		tm->tm_hour = (tm->tm_hour % 12) + 12;
		return 2;
	}

	if (match_string(date, "AM") == 2) {
		tm->tm_hour = (tm->tm_hour % 12) + 0;
		return 2;
	}

	/* BAD */
	return skip_alpha(date);
}
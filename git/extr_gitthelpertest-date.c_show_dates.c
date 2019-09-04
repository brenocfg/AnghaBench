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
typedef  int /*<<< orphan*/  timestamp_t ;
struct date_mode {int dummy; } ;

/* Variables and functions */
 int atoi (char*) ; 
 int /*<<< orphan*/  parse_date_format (char const*,struct date_mode*) ; 
 int /*<<< orphan*/  parse_timestamp (char const*,char**,int) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 char* show_date (int /*<<< orphan*/ ,int,struct date_mode*) ; 

__attribute__((used)) static void show_dates(const char **argv, const char *format)
{
	struct date_mode mode;

	parse_date_format(format, &mode);
	for (; *argv; argv++) {
		char *arg;
		timestamp_t t;
		int tz;

		/*
		 * Do not use our normal timestamp parsing here, as the point
		 * is to test the formatting code in isolation.
		 */
		t = parse_timestamp(*argv, &arg, 10);
		while (*arg == ' ')
			arg++;
		tz = atoi(arg);

		printf("%s -> %s\n", *argv, show_date(t, tz, &mode));
	}
}
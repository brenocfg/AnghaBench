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

/* Variables and functions */
 int /*<<< orphan*/  DATE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISO8601 ; 
 int /*<<< orphan*/  approxidate_relative (char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 char* show_date (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_approxidate(const char **argv)
{
	for (; *argv; argv++) {
		timestamp_t t;
		t = approxidate_relative(*argv);
		printf("%s -> %s\n", *argv, show_date(t, 0, DATE_MODE(ISO8601)));
	}
}
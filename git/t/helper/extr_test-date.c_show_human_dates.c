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

/* Variables and functions */
 int /*<<< orphan*/  DATE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HUMAN ; 
 int /*<<< orphan*/  atoi (char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 char* show_date (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_human_dates(const char **argv)
{
	for (; *argv; argv++) {
		time_t t = atoi(*argv);
		printf("%s -> %s\n", *argv, show_date(t, 0, DATE_MODE(HUMAN)));
	}
}
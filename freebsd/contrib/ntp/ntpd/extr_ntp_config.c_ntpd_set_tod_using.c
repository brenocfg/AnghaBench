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
typedef  int /*<<< orphan*/  line ;

/* Variables and functions */
 int /*<<< orphan*/  RO ; 
 int /*<<< orphan*/  set_sys_var (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
ntpd_set_tod_using(
	const char *which
	)
{
	char line[128];

	snprintf(line, sizeof(line), "settimeofday=\"%s\"", which);
	set_sys_var(line, strlen(line) + 1, RO);
}
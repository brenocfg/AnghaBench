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

/* Variables and functions */
 int /*<<< orphan*/  WHENSPEC_NOW ; 
 int /*<<< orphan*/  WHENSPEC_RAW ; 
 int /*<<< orphan*/  WHENSPEC_RFC2822 ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  whenspec ; 

__attribute__((used)) static void option_date_format(const char *fmt)
{
	if (!strcmp(fmt, "raw"))
		whenspec = WHENSPEC_RAW;
	else if (!strcmp(fmt, "rfc2822"))
		whenspec = WHENSPEC_RFC2822;
	else if (!strcmp(fmt, "now"))
		whenspec = WHENSPEC_NOW;
	else
		die("unknown --date-format argument %s", fmt);
}
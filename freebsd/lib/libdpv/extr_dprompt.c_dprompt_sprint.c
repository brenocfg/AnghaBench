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
 int /*<<< orphan*/  PROMPT_MAX ; 
 int /*<<< orphan*/  dprompt ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,char*,char const*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ use_color ; 

int
dprompt_sprint(char * restrict str, const char *prefix, const char *append)
{

	return (snprintf(str, PROMPT_MAX, "%s%s%s%s", use_color ? "\\Zn" : "",
	    prefix ? prefix : "", dprompt, append ? append : ""));
}
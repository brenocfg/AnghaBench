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
typedef  int /*<<< orphan*/  hx509_lock ;

/* Variables and functions */
 int HX509_UNKNOWN_LOCK_COMMAND ; 
 int /*<<< orphan*/  default_prompter ; 
 int /*<<< orphan*/  hx509_lock_add_password (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  hx509_lock_set_prompter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 

int
hx509_lock_command_string(hx509_lock lock, const char *string)
{
    if (strncasecmp(string, "PASS:", 5) == 0) {
	hx509_lock_add_password(lock, string + 5);
    } else if (strcasecmp(string, "PROMPT") == 0) {
	hx509_lock_set_prompter(lock, default_prompter, NULL);
    } else
	return HX509_UNKNOWN_LOCK_COMMAND;
    return 0;
}
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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  die_bad_number (char const*,char const*) ; 
 int /*<<< orphan*/  git_parse_ssize_t (char const*,int /*<<< orphan*/ *) ; 

ssize_t git_config_ssize_t(const char *name, const char *value)
{
	ssize_t ret;
	if (!git_parse_ssize_t(value, &ret))
		die_bad_number(name, value);
	return ret;
}
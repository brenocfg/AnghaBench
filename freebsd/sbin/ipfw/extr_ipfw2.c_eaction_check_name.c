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
 int EINVAL ; 
 scalar_t__ ipfw_check_object_name (char const*) ; 
 int match_token (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  rule_action_params ; 
 int /*<<< orphan*/  rule_actions ; 

__attribute__((used)) static int
eaction_check_name(const char *name)
{

	if (ipfw_check_object_name(name) != 0)
		return (EINVAL);
	/* Restrict some 'special' names */
	if (match_token(rule_actions, name) != -1 &&
	    match_token(rule_action_params, name) != -1)
		return (EINVAL);
	return (0);
}
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
struct string_list {int dummy; } ;

/* Variables and functions */
 struct string_list const* repo_config_get_value_multi (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  the_repository ; 

const struct string_list *git_config_get_value_multi(const char *key)
{
	return repo_config_get_value_multi(the_repository, key);
}
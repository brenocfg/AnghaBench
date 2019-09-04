#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct string_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  util; } ;

/* Variables and functions */
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 TYPE_1__* string_list_append (struct string_list*,char const*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int get_alias(const char *var, const char *value, void *data)
{
	struct string_list *list = data;

	if (skip_prefix(var, "alias.", &var))
		string_list_append(list, var)->util = xstrdup(value);

	return 0;
}
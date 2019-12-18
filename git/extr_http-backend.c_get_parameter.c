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
struct string_list_item {char const* util; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_parameters () ; 
 struct string_list_item* string_list_lookup (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static const char *get_parameter(const char *name)
{
	struct string_list_item *i;
	i = string_list_lookup(get_parameters(), name);
	return i ? i->util : NULL;
}
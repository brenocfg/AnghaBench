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
 int /*<<< orphan*/  string_list_append_nodup (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrfmt (char*,char const*,char const*) ; 

__attribute__((used)) static inline void list_config_item(struct string_list *list,
				    const char *prefix,
				    const char *str)
{
	string_list_append_nodup(list, xstrfmt("%s.%s", prefix, str));
}
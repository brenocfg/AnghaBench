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
struct string_list_item {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int starts_with (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int prefix_cb(struct string_list_item *item, void *cb_data)
{
	const char *prefix = (const char *)cb_data;
	return starts_with(item->string, prefix);
}
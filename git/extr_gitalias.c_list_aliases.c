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
struct config_alias_data {struct string_list* member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_alias_cb ; 
 int /*<<< orphan*/  read_early_config (int /*<<< orphan*/ ,struct config_alias_data*) ; 

void list_aliases(struct string_list *list)
{
	struct config_alias_data data = { NULL, NULL, list };

	read_early_config(config_alias_cb, &data);
}
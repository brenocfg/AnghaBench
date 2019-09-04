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
struct config_store_data {int /*<<< orphan*/ * seen; int /*<<< orphan*/ * parsed; int /*<<< orphan*/ * value_regex; int /*<<< orphan*/ * key; } ;

/* Variables and functions */
 int /*<<< orphan*/ * CONFIG_REGEX_NONE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct config_store_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void config_store_data_clear(struct config_store_data *store)
{
	free(store->key);
	if (store->value_regex != NULL &&
	    store->value_regex != CONFIG_REGEX_NONE) {
		regfree(store->value_regex);
		free(store->value_regex);
	}
	free(store->parsed);
	free(store->seen);
	memset(store, 0, sizeof(*store));
}
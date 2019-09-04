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
struct config_set_element {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_set_element_cmp(const void *unused_cmp_data,
				  const void *entry,
				  const void *entry_or_key,
				  const void *unused_keydata)
{
	const struct config_set_element *e1 = entry;
	const struct config_set_element *e2 = entry_or_key;

	return strcmp(e1->key, e2->key);
}
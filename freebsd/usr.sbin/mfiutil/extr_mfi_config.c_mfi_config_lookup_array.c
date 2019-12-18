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
typedef  scalar_t__ uint16_t ;
struct mfi_config_data {int array_count; int /*<<< orphan*/  array_size; scalar_t__ array; } ;
struct mfi_array {scalar_t__ array_ref; } ;

/* Variables and functions */

__attribute__((used)) static struct mfi_array *
mfi_config_lookup_array(struct mfi_config_data *config, uint16_t array_ref)
{
	struct mfi_array *ar;
	char *p;
	int i;

	p = (char *)config->array;
	for (i = 0; i < config->array_count; i++) {
		ar = (struct mfi_array *)p;
		if (ar->array_ref == array_ref)
			return (ar);
		p += config->array_size;
	}

	return (NULL);
}
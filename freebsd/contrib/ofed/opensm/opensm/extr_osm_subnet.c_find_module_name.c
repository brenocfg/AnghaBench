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
typedef  size_t uint8_t ;

/* Variables and functions */
 size_t MOD_NAME_STR_UNKNOWN_VAL ; 
 int /*<<< orphan*/ * module_name_str ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_module_name(const char *name, uint8_t *file_id)
{
	uint8_t i;

	for (i = 0; i < MOD_NAME_STR_UNKNOWN_VAL; i++) {
		if (strcmp(name, module_name_str[i]) == 0) {
			if (file_id)
				*file_id = i;
			return 0;
		}
	}
	return 1;
}
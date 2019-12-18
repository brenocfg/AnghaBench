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
struct TYPE_2__ {int flag; int /*<<< orphan*/ * flag_name; } ;

/* Variables and functions */
 TYPE_1__* flags_table ; 
 int /*<<< orphan*/ * strstr (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_flags(const char *entry)
{
	int	i;
	int	result = 0;

	for (i = 0; flags_table[i].flag_name != NULL; i++)
		if (strstr(entry, flags_table[i].flag_name) != NULL)
			result |= flags_table[i].flag;

	return (result);
}
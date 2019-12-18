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

/* Variables and functions */
 scalar_t__* bnxt_hash_types ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 

__attribute__((used)) static int bnxt_get_rss_type_str_bit(char *str)
{
	int i;

	for (i=0; bnxt_hash_types[i]; i++)
		if (strcmp(bnxt_hash_types[i], str) == 0)
			return i;

	return -1;
}
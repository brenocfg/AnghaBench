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
 char const* FST_NAME_UNKNOWN ; 

const char * fst_get_str_name(unsigned index, const char *names[],
			      size_t names_size)
{
	if (index >= names_size || !names[index])
		return FST_NAME_UNKNOWN;
	return names[index];
}
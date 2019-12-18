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
 int /*<<< orphan*/  BHND_NVRAM_TYPE_STRING_ARRAY ; 
 char const* bhnd_nvram_value_array_next (char const*,size_t,int /*<<< orphan*/ ,char const*,size_t*) ; 

const char *
bhnd_nvram_string_array_next(const char *inp, size_t ilen, const char *prev,
    size_t *olen)
{
	return (bhnd_nvram_value_array_next(inp, ilen,
	    BHND_NVRAM_TYPE_STRING_ARRAY, prev, olen));
}
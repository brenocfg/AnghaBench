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
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_TYPE_STRING_ARRAY ; 
 int nvlist_add_common (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char* const*) ; 

int
nvlist_add_string_array(nvlist_t *nvl, const char *name,
    char *const *a, uint_t n)
{
	return (nvlist_add_common(nvl, name, DATA_TYPE_STRING_ARRAY, n, a));
}
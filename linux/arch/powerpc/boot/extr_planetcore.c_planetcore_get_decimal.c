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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 char* planetcore_get_key (char const*,char const*) ; 
 int /*<<< orphan*/  strtoull (char const*,int /*<<< orphan*/ *,int) ; 

int planetcore_get_decimal(const char *table, const char *key, u64 *val)
{
	const char *str = planetcore_get_key(table, key);
	if (!str)
		return 0;

	*val = strtoull(str, NULL, 10);
	return 1;
}
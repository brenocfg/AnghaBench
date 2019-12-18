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
 char* _citrus_lookup_simple (char const*,char const*,char*,size_t,int) ; 

__attribute__((used)) static __inline const char *
_citrus_lookup_alias(const char *path, const char *key, char *buf, size_t n,
    int ignore_case)
{
	const char *ret;

	ret = _citrus_lookup_simple(path, key, buf, n, ignore_case);
	if (ret == NULL)
		ret = key;

	return (ret);
}
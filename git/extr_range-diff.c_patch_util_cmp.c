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
struct patch_util {char const* diff; } ;

/* Variables and functions */
 int strcmp (char const*,char const*) ; 

__attribute__((used)) static int patch_util_cmp(const void *dummy, const struct patch_util *a,
			  const struct patch_util *b, const char *keydata)
{
	return strcmp(a->diff, keydata ? keydata : b->diff);
}
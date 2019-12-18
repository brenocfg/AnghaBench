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
struct sortedcache_magic_key {int offset; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int sortedcache_magic_cmp(const void *key, const void *value)
{
	const struct sortedcache_magic_key *magic = key;
	const char *value_key = ((const char *)value) + magic->offset;
	return strcmp(magic->key, value_key);
}
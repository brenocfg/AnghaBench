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
struct test_entry {char const* key; } ;

/* Variables and functions */
 int strcasecmp (char const*,char const*) ; 
 int strcmp (char const*,char const*) ; 

__attribute__((used)) static int test_entry_cmp(const void *cmp_data,
			  const void *entry,
			  const void *entry_or_key,
			  const void *keydata)
{
	const int ignore_case = cmp_data ? *((int *)cmp_data) : 0;
	const struct test_entry *e1 = entry;
	const struct test_entry *e2 = entry_or_key;
	const char *key = keydata;

	if (ignore_case)
		return strcasecmp(e1->key, key ? key : e2->key);
	else
		return strcmp(e1->key, key ? key : e2->key);
}
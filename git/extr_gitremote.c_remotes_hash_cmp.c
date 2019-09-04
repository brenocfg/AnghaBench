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
struct remotes_hash_key {size_t len; int /*<<< orphan*/  str; } ;
struct remote {scalar_t__* name; } ;

/* Variables and functions */
 int strcmp (scalar_t__*,scalar_t__*) ; 
 scalar_t__ strncmp (scalar_t__*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int remotes_hash_cmp(const void *unused_cmp_data,
			    const void *entry,
			    const void *entry_or_key,
			    const void *keydata)
{
	const struct remote *a = entry;
	const struct remote *b = entry_or_key;
	const struct remotes_hash_key *key = keydata;

	if (key)
		return strncmp(a->name, key->str, key->len) || a->name[key->len];
	else
		return strcmp(a->name, b->name);
}
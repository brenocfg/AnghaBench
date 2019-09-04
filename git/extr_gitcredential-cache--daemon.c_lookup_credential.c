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
struct credential {int dummy; } ;
struct credential_cache_entry {struct credential item; } ;

/* Variables and functions */
 scalar_t__ credential_match (struct credential const*,struct credential*) ; 
 struct credential_cache_entry* entries ; 
 int entries_nr ; 

__attribute__((used)) static struct credential_cache_entry *lookup_credential(const struct credential *c)
{
	int i;
	for (i = 0; i < entries_nr; i++) {
		struct credential *e = &entries[i].item;
		if (credential_match(c, e))
			return &entries[i];
	}
	return NULL;
}
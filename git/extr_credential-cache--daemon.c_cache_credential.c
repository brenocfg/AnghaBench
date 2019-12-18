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
struct credential_cache_entry {scalar_t__ expiration; int /*<<< orphan*/  item; } ;
struct credential {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct credential_cache_entry*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct credential_cache_entry* entries ; 
 int /*<<< orphan*/  entries_alloc ; 
 scalar_t__ entries_nr ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct credential*,int) ; 
 int /*<<< orphan*/  memset (struct credential*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cache_credential(struct credential *c, int timeout)
{
	struct credential_cache_entry *e;

	ALLOC_GROW(entries, entries_nr + 1, entries_alloc);
	e = &entries[entries_nr++];

	/* take ownership of pointers */
	memcpy(&e->item, c, sizeof(*c));
	memset(c, 0, sizeof(*c));
	e->expiration = time(NULL) + timeout;
}
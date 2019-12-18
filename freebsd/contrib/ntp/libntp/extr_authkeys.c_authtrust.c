#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct TYPE_4__ {void* lifetime; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ symkey ;
typedef  int /*<<< orphan*/  keyid_t ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_TRUSTED ; 
 int /*<<< orphan*/  allocsymkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* auth_findkey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  authcache_flush_id (int /*<<< orphan*/ ) ; 
 void* current_time ; 
 int /*<<< orphan*/  freesymkey (TYPE_1__*) ; 

void
authtrust(
	keyid_t		id,
	u_long		trust
	)
{
	symkey *	sk;
	u_long		lifetime;

	/*
	 * Search bin for key; if it does not exist and is untrusted,
	 * forget it.
	 */

	sk = auth_findkey(id);
	if (!trust && sk == NULL)
		return;

	/*
	 * There are two conditions remaining. Either it does not
	 * exist and is to be trusted or it does exist and is or is
	 * not to be trusted.
	 */	
	if (sk != NULL) {
		/*
		 * Key exists. If it is to be trusted, say so and update
		 * its lifetime. If no longer trusted, return it to the
		 * free list. Flush the cache first to be sure there are
		 * no discrepancies.
		 */
		authcache_flush_id(id);
		if (trust > 0) {
			sk->flags |= KEY_TRUSTED;
			if (trust > 1)
				sk->lifetime = current_time + trust;
			else
				sk->lifetime = 0;
		} else {
			freesymkey(sk);
		}
		return;
	}

	/*
	 * keyid is not present, but the is to be trusted.  We allocate
	 * a new key, but do not specify a key type or secret.
	 */
	if (trust > 1) {
		lifetime = current_time + trust;
	} else {
		lifetime = 0;
	}
	allocsymkey(id, KEY_TRUSTED, 0, lifetime, 0, NULL, NULL);
}
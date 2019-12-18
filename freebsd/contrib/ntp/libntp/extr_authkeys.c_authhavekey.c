#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ type; int flags; scalar_t__ keyid; int /*<<< orphan*/  keyacclist; int /*<<< orphan*/  secretsize; int /*<<< orphan*/  secret; } ;
typedef  TYPE_1__ symkey ;
typedef  scalar_t__ keyid_t ;

/* Variables and functions */
 int FALSE ; 
 int KEY_TRUSTED ; 
 int TRUE ; 
 TYPE_1__* auth_findkey (scalar_t__) ; 
 int /*<<< orphan*/  authkeylookups ; 
 int /*<<< orphan*/  authkeynotfound ; 
 int /*<<< orphan*/  authkeyuncached ; 
 int /*<<< orphan*/  authnokey ; 
 int cache_flags ; 
 int /*<<< orphan*/  cache_keyacclist ; 
 scalar_t__ cache_keyid ; 
 int /*<<< orphan*/  cache_secret ; 
 int /*<<< orphan*/  cache_secretsize ; 
 scalar_t__ cache_type ; 

int
authhavekey(
	keyid_t		id
	)
{
	symkey *	sk;

	authkeylookups++;
	if (0 == id || cache_keyid == id)
		return !!(KEY_TRUSTED & cache_flags);

	/*
	 * Search the bin for the key. If not found, or found but the key
	 * type is zero, somebody marked it trusted without specifying a
	 * key or key type. In this case consider the key missing.
	 */
	authkeyuncached++;
	sk = auth_findkey(id);
	if ((sk == NULL) || (sk->type == 0)) {
		authkeynotfound++;
		return FALSE;
	}

	/*
	 * If the key is not trusted, the key is not considered found.
	 */
	if ( ! (KEY_TRUSTED & sk->flags)) {
		authnokey++;
		return FALSE;
	}

	/*
	 * The key is found and trusted. Initialize the key cache.
	 */
	cache_keyid = sk->keyid;
	cache_type = sk->type;
	cache_flags = sk->flags;
	cache_secret = sk->secret;
	cache_secretsize = sk->secretsize;
	cache_keyacclist = sk->keyacclist;

	return TRUE;
}
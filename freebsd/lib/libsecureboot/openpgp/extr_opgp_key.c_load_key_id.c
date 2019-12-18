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
typedef  int /*<<< orphan*/  OpenPGP_key ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PRINTF (int,char*) ; 
 int /*<<< orphan*/ * load_trusted_key_id (char const*) ; 
 int /*<<< orphan*/ * openpgp_trust_get (char const*) ; 

OpenPGP_key *
load_key_id(const char *keyID)
{
	OpenPGP_key *key;

	key = openpgp_trust_get(keyID);
#ifndef _STANDALONE
	if (!key)
		key = load_trusted_key_id(keyID);
#endif
	DEBUG_PRINTF(2, ("load_key_id(%s): %s\n", keyID, key ? "found" : "nope"));
	return (key);
}
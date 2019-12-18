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
typedef  int /*<<< orphan*/  key_ref_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int KEY_ALLOC_BUILT_IN ; 
 int KEY_ALLOC_NOT_IN_QUOTA ; 
 int KEY_POS_ALL ; 
 int KEY_POS_SETATTR ; 
 int KEY_USR_VIEW ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blacklist_keyring ; 
 int /*<<< orphan*/  key_create_or_update (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  make_key_ref (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

int mark_hash_blacklisted(const char *hash)
{
	key_ref_t key;

	key = key_create_or_update(make_key_ref(blacklist_keyring, true),
				   "blacklist",
				   hash,
				   NULL,
				   0,
				   ((KEY_POS_ALL & ~KEY_POS_SETATTR) |
				    KEY_USR_VIEW),
				   KEY_ALLOC_NOT_IN_QUOTA |
				   KEY_ALLOC_BUILT_IN);
	if (IS_ERR(key)) {
		pr_err("Problem blacklisting hash (%ld)\n", PTR_ERR(key));
		return PTR_ERR(key);
	}
	return 0;
}
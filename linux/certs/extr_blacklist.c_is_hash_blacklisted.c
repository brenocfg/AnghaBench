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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  key_ref_t ;

/* Variables and functions */
 int EKEYREJECTED ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bin2hex (char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  blacklist_keyring ; 
 int /*<<< orphan*/  key_ref_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_type_blacklist ; 
 int /*<<< orphan*/  keyring_search (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_key_ref (int /*<<< orphan*/ ,int) ; 
 char* memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

int is_hash_blacklisted(const u8 *hash, size_t hash_len, const char *type)
{
	key_ref_t kref;
	size_t type_len = strlen(type);
	char *buffer, *p;
	int ret = 0;

	buffer = kmalloc(type_len + 1 + hash_len * 2 + 1, GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;
	p = memcpy(buffer, type, type_len);
	p += type_len;
	*p++ = ':';
	bin2hex(p, hash, hash_len);
	p += hash_len * 2;
	*p = 0;

	kref = keyring_search(make_key_ref(blacklist_keyring, true),
			      &key_type_blacklist, buffer, false);
	if (!IS_ERR(kref)) {
		key_ref_put(kref);
		ret = -EKEYREJECTED;
	}

	kfree(buffer);
	return ret;
}
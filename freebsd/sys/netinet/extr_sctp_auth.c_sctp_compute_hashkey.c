#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_10__ {scalar_t__ keylen; int /*<<< orphan*/ * key; } ;
typedef  TYPE_1__ sctp_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* sctp_alloc_key (scalar_t__) ; 
 scalar_t__ sctp_compare_key (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ sctp_get_keylen (TYPE_1__*) ; 

sctp_key_t *
sctp_compute_hashkey(sctp_key_t *key1, sctp_key_t *key2, sctp_key_t *shared)
{
	uint32_t keylen;
	sctp_key_t *new_key;
	uint8_t *key_ptr;

	keylen = sctp_get_keylen(key1) + sctp_get_keylen(key2) +
	    sctp_get_keylen(shared);

	if (keylen > 0) {
		/* get space for the new key */
		new_key = sctp_alloc_key(keylen);
		if (new_key == NULL) {
			/* out of memory */
			return (NULL);
		}
		new_key->keylen = keylen;
		key_ptr = new_key->key;
	} else {
		/* all keys empty/null?! */
		return (NULL);
	}

	/* concatenate the keys */
	if (sctp_compare_key(key1, key2) <= 0) {
		/* key is shared + key1 + key2 */
		if (sctp_get_keylen(shared)) {
			memcpy(key_ptr, shared->key, shared->keylen);
			key_ptr += shared->keylen;
		}
		if (sctp_get_keylen(key1)) {
			memcpy(key_ptr, key1->key, key1->keylen);
			key_ptr += key1->keylen;
		}
		if (sctp_get_keylen(key2)) {
			memcpy(key_ptr, key2->key, key2->keylen);
		}
	} else {
		/* key is shared + key2 + key1 */
		if (sctp_get_keylen(shared)) {
			memcpy(key_ptr, shared->key, shared->keylen);
			key_ptr += shared->keylen;
		}
		if (sctp_get_keylen(key2)) {
			memcpy(key_ptr, key2->key, key2->keylen);
			key_ptr += key2->keylen;
		}
		if (sctp_get_keylen(key1)) {
			memcpy(key_ptr, key1->key, key1->keylen);
		}
	}
	return (new_key);
}
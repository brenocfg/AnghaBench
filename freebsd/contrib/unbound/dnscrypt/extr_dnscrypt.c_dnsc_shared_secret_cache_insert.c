#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct shared_secret_cache_key* data; struct shared_secret_cache_key* key; int /*<<< orphan*/  hash; int /*<<< orphan*/  lock; } ;
struct shared_secret_cache_key {TYPE_1__ entry; struct shared_secret_cache_key* key; } ;
typedef  struct shared_secret_cache_key uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct slabhash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DNSCRYPT_SHARED_SECRET_KEY_LENGTH ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  crypto_box_BEFORENMBYTES ; 
 int /*<<< orphan*/  free (struct shared_secret_cache_key*) ; 
 int /*<<< orphan*/  lock_rw_init (int /*<<< orphan*/ *) ; 
 struct shared_secret_cache_key* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct shared_secret_cache_key*,struct shared_secret_cache_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slabhash_insert (struct slabhash*,int /*<<< orphan*/ ,TYPE_1__*,struct shared_secret_cache_key*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dnsc_shared_secret_cache_insert(struct slabhash *cache,
                                uint8_t key[DNSCRYPT_SHARED_SECRET_KEY_LENGTH],
                                uint32_t hash,
                                uint8_t nmkey[crypto_box_BEFORENMBYTES])
{
    struct shared_secret_cache_key* k =
        (struct shared_secret_cache_key*)calloc(1, sizeof(*k));
    uint8_t* d = malloc(crypto_box_BEFORENMBYTES);
    if(!k || !d) {
        free(k);
        free(d);
        return;
    }
    memcpy(d, nmkey, crypto_box_BEFORENMBYTES);
    lock_rw_init(&k->entry.lock);
    memcpy(k->key, key, DNSCRYPT_SHARED_SECRET_KEY_LENGTH);
    k->entry.hash = hash;
    k->entry.key = k;
    k->entry.data = d;
    slabhash_insert(cache,
                    hash, &k->entry,
                    d,
                    NULL);
}
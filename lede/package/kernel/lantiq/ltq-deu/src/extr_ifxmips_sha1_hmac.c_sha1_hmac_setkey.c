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
struct sha1_hmac_ctx {unsigned int keylen; int /*<<< orphan*/  key; } ;
struct deu_hash_t {int KIDX; } ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HASH_START ; 
 unsigned int SHA1_HMAC_MAX_KEYLEN ; 
 struct sha1_hmac_ctx* crypto_shash_ctx (struct crypto_shash*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int sha1_hmac_setkey(struct crypto_shash *tfm, const u8 *key, unsigned int keylen)
{
    struct sha1_hmac_ctx *sctx = crypto_shash_ctx(tfm);
    volatile struct deu_hash_t *hashs = (struct deu_hash_t *) HASH_START;
    
    if (keylen > SHA1_HMAC_MAX_KEYLEN) {
	printk("Key length exceeds maximum key length\n");
	return -EINVAL;
    }

    //printk("Setting keys of len: %d\n", keylen);
     
    hashs->KIDX |= 0x80000000; //reset keys back to 0
    memcpy(&sctx->key, key, keylen);
    sctx->keylen = keylen;

    return 0;
         
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct crypto_stat_cipher {void* stat_err_cnt; void* stat_decrypt_tlen; void* stat_decrypt_cnt; void* stat_encrypt_tlen; void* stat_encrypt_cnt; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  err_cnt; int /*<<< orphan*/  decrypt_tlen; int /*<<< orphan*/  decrypt_cnt; int /*<<< orphan*/  encrypt_tlen; int /*<<< orphan*/  encrypt_cnt; } ;
struct TYPE_4__ {TYPE_1__ cipher; } ;
struct crypto_alg {TYPE_2__ stats; } ;
typedef  int /*<<< orphan*/  rcipher ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTOCFGA_STAT_CIPHER ; 
 void* atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct crypto_stat_cipher*,int /*<<< orphan*/ ,int) ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct crypto_stat_cipher*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int crypto_report_cipher(struct sk_buff *skb, struct crypto_alg *alg)
{
	struct crypto_stat_cipher rcipher;

	memset(&rcipher, 0, sizeof(rcipher));

	strscpy(rcipher.type, "cipher", sizeof(rcipher.type));

	rcipher.stat_encrypt_cnt = atomic64_read(&alg->stats.cipher.encrypt_cnt);
	rcipher.stat_encrypt_tlen = atomic64_read(&alg->stats.cipher.encrypt_tlen);
	rcipher.stat_decrypt_cnt =  atomic64_read(&alg->stats.cipher.decrypt_cnt);
	rcipher.stat_decrypt_tlen = atomic64_read(&alg->stats.cipher.decrypt_tlen);
	rcipher.stat_err_cnt =  atomic64_read(&alg->stats.cipher.err_cnt);

	return nla_put(skb, CRYPTOCFGA_STAT_CIPHER, sizeof(rcipher), &rcipher);
}
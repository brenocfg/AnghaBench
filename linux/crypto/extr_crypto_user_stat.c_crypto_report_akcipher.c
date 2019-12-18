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
struct crypto_stat_akcipher {void* stat_err_cnt; void* stat_verify_cnt; void* stat_sign_cnt; void* stat_decrypt_tlen; void* stat_decrypt_cnt; void* stat_encrypt_tlen; void* stat_encrypt_cnt; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  err_cnt; int /*<<< orphan*/  verify_cnt; int /*<<< orphan*/  sign_cnt; int /*<<< orphan*/  decrypt_tlen; int /*<<< orphan*/  decrypt_cnt; int /*<<< orphan*/  encrypt_tlen; int /*<<< orphan*/  encrypt_cnt; } ;
struct TYPE_4__ {TYPE_1__ akcipher; } ;
struct crypto_alg {TYPE_2__ stats; } ;
typedef  int /*<<< orphan*/  rakcipher ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTOCFGA_STAT_AKCIPHER ; 
 void* atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct crypto_stat_akcipher*,int /*<<< orphan*/ ,int) ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct crypto_stat_akcipher*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int crypto_report_akcipher(struct sk_buff *skb, struct crypto_alg *alg)
{
	struct crypto_stat_akcipher rakcipher;

	memset(&rakcipher, 0, sizeof(rakcipher));

	strscpy(rakcipher.type, "akcipher", sizeof(rakcipher.type));
	rakcipher.stat_encrypt_cnt = atomic64_read(&alg->stats.akcipher.encrypt_cnt);
	rakcipher.stat_encrypt_tlen = atomic64_read(&alg->stats.akcipher.encrypt_tlen);
	rakcipher.stat_decrypt_cnt = atomic64_read(&alg->stats.akcipher.decrypt_cnt);
	rakcipher.stat_decrypt_tlen = atomic64_read(&alg->stats.akcipher.decrypt_tlen);
	rakcipher.stat_sign_cnt = atomic64_read(&alg->stats.akcipher.sign_cnt);
	rakcipher.stat_verify_cnt = atomic64_read(&alg->stats.akcipher.verify_cnt);
	rakcipher.stat_err_cnt = atomic64_read(&alg->stats.akcipher.err_cnt);

	return nla_put(skb, CRYPTOCFGA_STAT_AKCIPHER,
		       sizeof(rakcipher), &rakcipher);
}
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
struct sk_buff {int dummy; } ;
struct crypto_report_cipher {int /*<<< orphan*/  max_keysize; int /*<<< orphan*/  min_keysize; int /*<<< orphan*/  blocksize; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  cia_max_keysize; int /*<<< orphan*/  cia_min_keysize; } ;
struct crypto_alg {TYPE_1__ cra_cipher; int /*<<< orphan*/  cra_blocksize; } ;
typedef  int /*<<< orphan*/  rcipher ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTOCFGA_REPORT_CIPHER ; 
 int /*<<< orphan*/  memset (struct crypto_report_cipher*,int /*<<< orphan*/ ,int) ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct crypto_report_cipher*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int crypto_report_cipher(struct sk_buff *skb, struct crypto_alg *alg)
{
	struct crypto_report_cipher rcipher;

	memset(&rcipher, 0, sizeof(rcipher));

	strscpy(rcipher.type, "cipher", sizeof(rcipher.type));

	rcipher.blocksize = alg->cra_blocksize;
	rcipher.min_keysize = alg->cra_cipher.cia_min_keysize;
	rcipher.max_keysize = alg->cra_cipher.cia_max_keysize;

	return nla_put(skb, CRYPTOCFGA_REPORT_CIPHER,
		       sizeof(rcipher), &rcipher);
}
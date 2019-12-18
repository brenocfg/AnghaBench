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
struct crypto_user_alg {int cru_flags; int /*<<< orphan*/  type; int /*<<< orphan*/  cru_refcnt; scalar_t__ cru_mask; scalar_t__ cru_type; int /*<<< orphan*/  cru_module_name; int /*<<< orphan*/  cru_driver_name; int /*<<< orphan*/  cru_name; } ;
struct crypto_report_larval {int cru_flags; int /*<<< orphan*/  type; int /*<<< orphan*/  cru_refcnt; scalar_t__ cru_mask; scalar_t__ cru_type; int /*<<< orphan*/  cru_module_name; int /*<<< orphan*/  cru_driver_name; int /*<<< orphan*/  cru_name; } ;
struct crypto_alg {char* cra_name; char* cra_driver_name; int cra_flags; TYPE_1__* cra_type; int /*<<< orphan*/  cra_priority; int /*<<< orphan*/  cra_refcnt; int /*<<< orphan*/  cra_module; } ;
typedef  int /*<<< orphan*/  rl ;
struct TYPE_2__ {scalar_t__ (* report ) (struct sk_buff*,struct crypto_alg*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTOCFGA_PRIORITY_VAL ; 
 int /*<<< orphan*/  CRYPTOCFGA_REPORT_LARVAL ; 
 int CRYPTO_ALG_LARVAL ; 
#define  CRYPTO_ALG_TYPE_CIPHER 129 
#define  CRYPTO_ALG_TYPE_COMPRESS 128 
 int CRYPTO_ALG_TYPE_MASK ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  crypto_report_cipher (struct sk_buff*,struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_report_comp (struct sk_buff*,struct crypto_alg*) ; 
 int /*<<< orphan*/  memset (struct crypto_user_alg*,int /*<<< orphan*/ ,int) ; 
 char* module_name (int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct crypto_user_alg*) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ stub1 (struct sk_buff*,struct crypto_alg*) ; 

__attribute__((used)) static int crypto_report_one(struct crypto_alg *alg,
			     struct crypto_user_alg *ualg, struct sk_buff *skb)
{
	memset(ualg, 0, sizeof(*ualg));

	strscpy(ualg->cru_name, alg->cra_name, sizeof(ualg->cru_name));
	strscpy(ualg->cru_driver_name, alg->cra_driver_name,
		sizeof(ualg->cru_driver_name));
	strscpy(ualg->cru_module_name, module_name(alg->cra_module),
		sizeof(ualg->cru_module_name));

	ualg->cru_type = 0;
	ualg->cru_mask = 0;
	ualg->cru_flags = alg->cra_flags;
	ualg->cru_refcnt = refcount_read(&alg->cra_refcnt);

	if (nla_put_u32(skb, CRYPTOCFGA_PRIORITY_VAL, alg->cra_priority))
		goto nla_put_failure;
	if (alg->cra_flags & CRYPTO_ALG_LARVAL) {
		struct crypto_report_larval rl;

		memset(&rl, 0, sizeof(rl));
		strscpy(rl.type, "larval", sizeof(rl.type));
		if (nla_put(skb, CRYPTOCFGA_REPORT_LARVAL, sizeof(rl), &rl))
			goto nla_put_failure;
		goto out;
	}

	if (alg->cra_type && alg->cra_type->report) {
		if (alg->cra_type->report(skb, alg))
			goto nla_put_failure;

		goto out;
	}

	switch (alg->cra_flags & (CRYPTO_ALG_TYPE_MASK | CRYPTO_ALG_LARVAL)) {
	case CRYPTO_ALG_TYPE_CIPHER:
		if (crypto_report_cipher(skb, alg))
			goto nla_put_failure;

		break;
	case CRYPTO_ALG_TYPE_COMPRESS:
		if (crypto_report_comp(skb, alg))
			goto nla_put_failure;

		break;
	}

out:
	return 0;

nla_put_failure:
	return -EMSGSIZE;
}
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
typedef  int /*<<< orphan*/  u32 ;
struct rtattr {int dummy; } ;
struct hash_alg_common {int dummy; } ;
struct crypto_alg {int dummy; } ;

/* Variables and functions */
 struct hash_alg_common* ERR_CAST (struct crypto_alg*) ; 
 scalar_t__ IS_ERR (struct crypto_alg*) ; 
 struct hash_alg_common* __crypto_hash_alg_common (struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_ahash_type ; 
 struct crypto_alg* crypto_attr_alg2 (struct rtattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct hash_alg_common *ahash_attr_alg(struct rtattr *rta, u32 type, u32 mask)
{
	struct crypto_alg *alg;

	alg = crypto_attr_alg2(rta, &crypto_ahash_type, type, mask);
	return IS_ERR(alg) ? ERR_CAST(alg) : __crypto_hash_alg_common(alg);
}
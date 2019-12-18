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
struct crypto_alg {int cra_flags; } ;

/* Variables and functions */
 int CRYPTO_ALG_LARVAL ; 

__attribute__((used)) static inline int crypto_is_larval(struct crypto_alg *alg)
{
	return alg->cra_flags & CRYPTO_ALG_LARVAL;
}
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
struct crypto_alg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aes_s390_algs_num ; 
 struct crypto_alg** aes_s390_algs_ptr ; 
 int crypto_register_alg (struct crypto_alg*) ; 

__attribute__((used)) static int aes_s390_register_alg(struct crypto_alg *alg)
{
	int ret;

	ret = crypto_register_alg(alg);
	if (!ret)
		aes_s390_algs_ptr[aes_s390_algs_num++] = alg;
	return ret;
}
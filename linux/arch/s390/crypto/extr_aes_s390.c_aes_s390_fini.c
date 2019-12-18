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

/* Variables and functions */
 scalar_t__ aes_s390_aead_alg ; 
 size_t aes_s390_algs_num ; 
 int /*<<< orphan*/ * aes_s390_algs_ptr ; 
 int /*<<< orphan*/  crypto_unregister_aead (scalar_t__) ; 
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ ) ; 
 scalar_t__ ctrblk ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 

__attribute__((used)) static void aes_s390_fini(void)
{
	while (aes_s390_algs_num--)
		crypto_unregister_alg(aes_s390_algs_ptr[aes_s390_algs_num]);
	if (ctrblk)
		free_page((unsigned long) ctrblk);

	if (aes_s390_aead_alg)
		crypto_unregister_aead(aes_s390_aead_alg);
}
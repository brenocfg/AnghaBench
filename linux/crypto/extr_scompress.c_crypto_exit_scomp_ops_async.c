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
struct crypto_tfm {int dummy; } ;
struct crypto_scomp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_scomp (struct crypto_scomp*) ; 
 int /*<<< orphan*/  crypto_scomp_free_scratches () ; 
 struct crypto_scomp** crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scomp_lock ; 
 int /*<<< orphan*/  scomp_scratch_users ; 

__attribute__((used)) static void crypto_exit_scomp_ops_async(struct crypto_tfm *tfm)
{
	struct crypto_scomp **ctx = crypto_tfm_ctx(tfm);

	crypto_free_scomp(*ctx);

	mutex_lock(&scomp_lock);
	if (!--scomp_scratch_users)
		crypto_scomp_free_scratches();
	mutex_unlock(&scomp_lock);
}
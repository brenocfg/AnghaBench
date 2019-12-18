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

/* Variables and functions */
 int crypto_scomp_alloc_scratches () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scomp_lock ; 
 int /*<<< orphan*/  scomp_scratch_users ; 

__attribute__((used)) static int crypto_scomp_init_tfm(struct crypto_tfm *tfm)
{
	int ret = 0;

	mutex_lock(&scomp_lock);
	if (!scomp_scratch_users++)
		ret = crypto_scomp_alloc_scratches();
	mutex_unlock(&scomp_lock);

	return ret;
}
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
struct crypto_spawn {struct crypto_alg* alg; int /*<<< orphan*/  list; int /*<<< orphan*/  mask; struct crypto_instance* inst; } ;
struct crypto_instance {int dummy; } ;
struct crypto_alg {int /*<<< orphan*/  cra_users; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_alg_sem ; 
 int /*<<< orphan*/  crypto_is_moribund (struct crypto_alg*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int crypto_init_spawn(struct crypto_spawn *spawn, struct crypto_alg *alg,
		      struct crypto_instance *inst, u32 mask)
{
	int err = -EAGAIN;

	if (WARN_ON_ONCE(inst == NULL))
		return -EINVAL;

	spawn->inst = inst;
	spawn->mask = mask;

	down_write(&crypto_alg_sem);
	if (!crypto_is_moribund(alg)) {
		list_add(&spawn->list, &alg->cra_users);
		spawn->alg = alg;
		err = 0;
	}
	up_write(&crypto_alg_sem);

	return err;
}
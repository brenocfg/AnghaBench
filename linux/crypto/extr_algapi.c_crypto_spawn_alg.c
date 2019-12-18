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
struct crypto_spawn {struct crypto_alg* alg; } ;
struct crypto_alg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 struct crypto_alg* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_alg_sem ; 
 struct crypto_alg* crypto_mod_get (struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_shoot_alg (struct crypto_alg*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct crypto_alg *crypto_spawn_alg(struct crypto_spawn *spawn)
{
	struct crypto_alg *alg;
	struct crypto_alg *alg2;

	down_read(&crypto_alg_sem);
	alg = spawn->alg;
	alg2 = alg;
	if (alg2)
		alg2 = crypto_mod_get(alg2);
	up_read(&crypto_alg_sem);

	if (!alg2) {
		if (alg)
			crypto_shoot_alg(alg);
		return ERR_PTR(-EAGAIN);
	}

	return alg;
}
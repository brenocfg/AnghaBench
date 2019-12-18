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
typedef  void crypto_tfm ;
struct crypto_spawn {int /*<<< orphan*/  frontend; } ;
typedef  void crypto_alg ;

/* Variables and functions */
 void* ERR_CAST (void*) ; 
 scalar_t__ IS_ERR (void*) ; 
 void* crypto_create_tfm (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_mod_put (void*) ; 
 void* crypto_spawn_alg (struct crypto_spawn*) ; 

void *crypto_spawn_tfm2(struct crypto_spawn *spawn)
{
	struct crypto_alg *alg;
	struct crypto_tfm *tfm;

	alg = crypto_spawn_alg(spawn);
	if (IS_ERR(alg))
		return ERR_CAST(alg);

	tfm = crypto_create_tfm(alg, spawn->frontend);
	if (IS_ERR(tfm))
		goto out_put_alg;

	return tfm;

out_put_alg:
	crypto_mod_put(alg);
	return tfm;
}
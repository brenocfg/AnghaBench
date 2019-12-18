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
struct atmel_tdes_dev {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int crypto_register_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tdes_algs ; 

__attribute__((used)) static int atmel_tdes_register_algs(struct atmel_tdes_dev *dd)
{
	int err, i, j;

	for (i = 0; i < ARRAY_SIZE(tdes_algs); i++) {
		err = crypto_register_alg(&tdes_algs[i]);
		if (err)
			goto err_tdes_algs;
	}

	return 0;

err_tdes_algs:
	for (j = 0; j < i; j++)
		crypto_unregister_alg(&tdes_algs[j]);

	return err;
}
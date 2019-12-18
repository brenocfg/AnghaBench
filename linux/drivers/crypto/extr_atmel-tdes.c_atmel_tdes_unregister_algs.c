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
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tdes_algs ; 

__attribute__((used)) static void atmel_tdes_unregister_algs(struct atmel_tdes_dev *dd)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(tdes_algs); i++)
		crypto_unregister_alg(&tdes_algs[i]);
}
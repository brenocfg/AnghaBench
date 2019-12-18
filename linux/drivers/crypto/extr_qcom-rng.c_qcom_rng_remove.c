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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_unregister_rng (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_rng_alg ; 
 int /*<<< orphan*/ * qcom_rng_dev ; 

__attribute__((used)) static int qcom_rng_remove(struct platform_device *pdev)
{
	crypto_unregister_rng(&qcom_rng_alg);

	qcom_rng_dev = NULL;

	return 0;
}
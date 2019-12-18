#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cra_name; int /*<<< orphan*/  cra_driver_name; } ;
struct shash_alg {TYPE_1__ base; } ;

/* Variables and functions */
 int crypto_unregister_shash (struct shash_alg*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int crypto_unregister_shashes(struct shash_alg *algs, int count)
{
	int i, ret;

	for (i = count - 1; i >= 0; --i) {
		ret = crypto_unregister_shash(&algs[i]);
		if (ret)
			pr_err("Failed to unregister %s %s: %d\n",
			       algs[i].base.cra_driver_name,
			       algs[i].base.cra_name, ret);
	}

	return 0;
}
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
struct qce_device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ahash_def ; 
 int qce_ahash_register_one (int /*<<< orphan*/ *,struct qce_device*) ; 
 int /*<<< orphan*/  qce_ahash_unregister (struct qce_device*) ; 

__attribute__((used)) static int qce_ahash_register(struct qce_device *qce)
{
	int ret, i;

	for (i = 0; i < ARRAY_SIZE(ahash_def); i++) {
		ret = qce_ahash_register_one(&ahash_def[i], qce);
		if (ret)
			goto err;
	}

	return 0;
err:
	qce_ahash_unregister(qce);
	return ret;
}
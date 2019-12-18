#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct hash_device_data {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  cra_driver_name; } ;
struct TYPE_8__ {TYPE_1__ base; } ;
struct TYPE_10__ {TYPE_2__ halg; } ;
struct TYPE_9__ {TYPE_4__ hash; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int crypto_register_ahash (TYPE_4__*) ; 
 int /*<<< orphan*/  crypto_unregister_ahash (TYPE_4__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* hash_algs ; 

__attribute__((used)) static int ahash_algs_register_all(struct hash_device_data *device_data)
{
	int ret;
	int i;
	int count;

	for (i = 0; i < ARRAY_SIZE(hash_algs); i++) {
		ret = crypto_register_ahash(&hash_algs[i].hash);
		if (ret) {
			count = i;
			dev_err(device_data->dev, "%s: alg registration failed\n",
				hash_algs[i].hash.halg.base.cra_driver_name);
			goto unreg;
		}
	}
	return 0;
unreg:
	for (i = 0; i < count; i++)
		crypto_unregister_ahash(&hash_algs[i].hash);
	return ret;
}
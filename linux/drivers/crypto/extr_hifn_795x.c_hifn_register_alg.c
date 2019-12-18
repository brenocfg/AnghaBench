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
struct hifn_device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int hifn_alg_alloc (struct hifn_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hifn_alg_templates ; 
 int /*<<< orphan*/  hifn_unregister_alg (struct hifn_device*) ; 

__attribute__((used)) static int hifn_register_alg(struct hifn_device *dev)
{
	int i, err;

	for (i = 0; i < ARRAY_SIZE(hifn_alg_templates); ++i) {
		err = hifn_alg_alloc(dev, &hifn_alg_templates[i]);
		if (err)
			goto err_out_exit;
	}

	return 0;

err_out_exit:
	hifn_unregister_alg(dev);
	return err;
}
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
struct s5p_aes_dev {int use_hash; scalar_t__ clk; scalar_t__ pclk; int /*<<< orphan*/  hash_tasklet; TYPE_1__* res; int /*<<< orphan*/  tasklet; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {int end; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENODEV ; 
 int /*<<< orphan*/ * algs ; 
 int /*<<< orphan*/ * algs_sha1_md5_sha256 ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  crypto_unregister_ahash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 
 struct s5p_aes_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/ * s5p_dev ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s5p_aes_remove(struct platform_device *pdev)
{
	struct s5p_aes_dev *pdata = platform_get_drvdata(pdev);
	int i;

	if (!pdata)
		return -ENODEV;

	for (i = 0; i < ARRAY_SIZE(algs); i++)
		crypto_unregister_alg(&algs[i]);

	tasklet_kill(&pdata->tasklet);
	if (pdata->use_hash) {
		for (i = ARRAY_SIZE(algs_sha1_md5_sha256) - 1; i >= 0; i--)
			crypto_unregister_ahash(&algs_sha1_md5_sha256[i]);

		pdata->res->end -= 0x300;
		tasklet_kill(&pdata->hash_tasklet);
		pdata->use_hash = false;
	}

	if (pdata->pclk)
		clk_disable_unprepare(pdata->pclk);

	clk_disable_unprepare(pdata->clk);
	s5p_dev = NULL;

	return 0;
}
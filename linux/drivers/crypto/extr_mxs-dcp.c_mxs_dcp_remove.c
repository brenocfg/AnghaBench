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
struct dcp {int caps; int /*<<< orphan*/  dcp_clk; int /*<<< orphan*/ * thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 size_t DCP_CHAN_CRYPTO ; 
 size_t DCP_CHAN_HASH_SHA ; 
 int MXS_DCP_CAPABILITY1_AES128 ; 
 int MXS_DCP_CAPABILITY1_SHA1 ; 
 int MXS_DCP_CAPABILITY1_SHA256 ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_unregister_ahash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_algs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcp_aes_algs ; 
 int /*<<< orphan*/  dcp_sha1_alg ; 
 int /*<<< orphan*/  dcp_sha256_alg ; 
 int /*<<< orphan*/ * global_sdcp ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 struct dcp* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxs_dcp_remove(struct platform_device *pdev)
{
	struct dcp *sdcp = platform_get_drvdata(pdev);

	if (sdcp->caps & MXS_DCP_CAPABILITY1_SHA256)
		crypto_unregister_ahash(&dcp_sha256_alg);

	if (sdcp->caps & MXS_DCP_CAPABILITY1_SHA1)
		crypto_unregister_ahash(&dcp_sha1_alg);

	if (sdcp->caps & MXS_DCP_CAPABILITY1_AES128)
		crypto_unregister_algs(dcp_aes_algs, ARRAY_SIZE(dcp_aes_algs));

	kthread_stop(sdcp->thread[DCP_CHAN_HASH_SHA]);
	kthread_stop(sdcp->thread[DCP_CHAN_CRYPTO]);

	clk_disable_unprepare(sdcp->dcp_clk);

	platform_set_drvdata(pdev, NULL);

	global_sdcp = NULL;

	return 0;
}
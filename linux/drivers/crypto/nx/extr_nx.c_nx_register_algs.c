#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nx_stats {int dummy; } ;
struct TYPE_4__ {scalar_t__ flags; int /*<<< orphan*/  status; } ;
struct TYPE_5__ {TYPE_1__ of; int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  NX_DEBUGFS_INIT (TYPE_2__*) ; 
 int /*<<< orphan*/  NX_FC_AES ; 
 int /*<<< orphan*/  NX_FC_SHA ; 
 int /*<<< orphan*/  NX_MODE_AES_CBC ; 
 int /*<<< orphan*/  NX_MODE_AES_CCM ; 
 int /*<<< orphan*/  NX_MODE_AES_CTR ; 
 int /*<<< orphan*/  NX_MODE_AES_ECB ; 
 int /*<<< orphan*/  NX_MODE_AES_GCM ; 
 int /*<<< orphan*/  NX_MODE_AES_XCBC_MAC ; 
 int /*<<< orphan*/  NX_MODE_SHA ; 
 scalar_t__ NX_OF_FLAG_MASK_READY ; 
 int /*<<< orphan*/  NX_OKAY ; 
 int NX_PROPS_SHA256 ; 
 int NX_PROPS_SHA512 ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nx_cbc_aes_alg ; 
 int /*<<< orphan*/  nx_ccm4309_aes_alg ; 
 int /*<<< orphan*/  nx_ccm_aes_alg ; 
 int /*<<< orphan*/  nx_ctr3686_aes_alg ; 
 TYPE_2__ nx_driver ; 
 int /*<<< orphan*/  nx_ecb_aes_alg ; 
 int /*<<< orphan*/  nx_gcm4106_aes_alg ; 
 int /*<<< orphan*/  nx_gcm_aes_alg ; 
 int nx_register_aead (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nx_register_alg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nx_register_shash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nx_shash_aes_xcbc_alg ; 
 int /*<<< orphan*/  nx_shash_sha256_alg ; 
 int /*<<< orphan*/  nx_shash_sha512_alg ; 
 int /*<<< orphan*/  nx_unregister_aead (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nx_unregister_alg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nx_unregister_shash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nx_register_algs(void)
{
	int rc = -1;

	if (nx_driver.of.flags != NX_OF_FLAG_MASK_READY)
		goto out;

	memset(&nx_driver.stats, 0, sizeof(struct nx_stats));

	NX_DEBUGFS_INIT(&nx_driver);

	nx_driver.of.status = NX_OKAY;

	rc = nx_register_alg(&nx_ecb_aes_alg, NX_FC_AES, NX_MODE_AES_ECB);
	if (rc)
		goto out;

	rc = nx_register_alg(&nx_cbc_aes_alg, NX_FC_AES, NX_MODE_AES_CBC);
	if (rc)
		goto out_unreg_ecb;

	rc = nx_register_alg(&nx_ctr3686_aes_alg, NX_FC_AES, NX_MODE_AES_CTR);
	if (rc)
		goto out_unreg_cbc;

	rc = nx_register_aead(&nx_gcm_aes_alg, NX_FC_AES, NX_MODE_AES_GCM);
	if (rc)
		goto out_unreg_ctr3686;

	rc = nx_register_aead(&nx_gcm4106_aes_alg, NX_FC_AES, NX_MODE_AES_GCM);
	if (rc)
		goto out_unreg_gcm;

	rc = nx_register_aead(&nx_ccm_aes_alg, NX_FC_AES, NX_MODE_AES_CCM);
	if (rc)
		goto out_unreg_gcm4106;

	rc = nx_register_aead(&nx_ccm4309_aes_alg, NX_FC_AES, NX_MODE_AES_CCM);
	if (rc)
		goto out_unreg_ccm;

	rc = nx_register_shash(&nx_shash_sha256_alg, NX_FC_SHA, NX_MODE_SHA,
			       NX_PROPS_SHA256);
	if (rc)
		goto out_unreg_ccm4309;

	rc = nx_register_shash(&nx_shash_sha512_alg, NX_FC_SHA, NX_MODE_SHA,
			       NX_PROPS_SHA512);
	if (rc)
		goto out_unreg_s256;

	rc = nx_register_shash(&nx_shash_aes_xcbc_alg,
			       NX_FC_AES, NX_MODE_AES_XCBC_MAC, -1);
	if (rc)
		goto out_unreg_s512;

	goto out;

out_unreg_s512:
	nx_unregister_shash(&nx_shash_sha512_alg, NX_FC_SHA, NX_MODE_SHA,
			    NX_PROPS_SHA512);
out_unreg_s256:
	nx_unregister_shash(&nx_shash_sha256_alg, NX_FC_SHA, NX_MODE_SHA,
			    NX_PROPS_SHA256);
out_unreg_ccm4309:
	nx_unregister_aead(&nx_ccm4309_aes_alg, NX_FC_AES, NX_MODE_AES_CCM);
out_unreg_ccm:
	nx_unregister_aead(&nx_ccm_aes_alg, NX_FC_AES, NX_MODE_AES_CCM);
out_unreg_gcm4106:
	nx_unregister_aead(&nx_gcm4106_aes_alg, NX_FC_AES, NX_MODE_AES_GCM);
out_unreg_gcm:
	nx_unregister_aead(&nx_gcm_aes_alg, NX_FC_AES, NX_MODE_AES_GCM);
out_unreg_ctr3686:
	nx_unregister_alg(&nx_ctr3686_aes_alg, NX_FC_AES, NX_MODE_AES_CTR);
out_unreg_cbc:
	nx_unregister_alg(&nx_cbc_aes_alg, NX_FC_AES, NX_MODE_AES_CBC);
out_unreg_ecb:
	nx_unregister_alg(&nx_ecb_aes_alg, NX_FC_AES, NX_MODE_AES_ECB);
out:
	return rc;
}
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
struct cc_drvdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cc_aead_free (struct cc_drvdata*) ; 
 int /*<<< orphan*/  cc_buffer_mgr_fini (struct cc_drvdata*) ; 
 int /*<<< orphan*/  cc_cipher_free (struct cc_drvdata*) ; 
 int /*<<< orphan*/  cc_clk_off (struct cc_drvdata*) ; 
 int /*<<< orphan*/  cc_debugfs_fini (struct cc_drvdata*) ; 
 int /*<<< orphan*/  cc_fips_fini (struct cc_drvdata*) ; 
 int /*<<< orphan*/  cc_hash_free (struct cc_drvdata*) ; 
 int /*<<< orphan*/  cc_pm_fini (struct cc_drvdata*) ; 
 int /*<<< orphan*/  cc_req_mgr_fini (struct cc_drvdata*) ; 
 int /*<<< orphan*/  cc_sram_mgr_fini (struct cc_drvdata*) ; 
 int /*<<< orphan*/  fini_cc_regs (struct cc_drvdata*) ; 
 scalar_t__ platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void cleanup_cc_resources(struct platform_device *plat_dev)
{
	struct cc_drvdata *drvdata =
		(struct cc_drvdata *)platform_get_drvdata(plat_dev);

	cc_aead_free(drvdata);
	cc_hash_free(drvdata);
	cc_cipher_free(drvdata);
	cc_pm_fini(drvdata);
	cc_buffer_mgr_fini(drvdata);
	cc_req_mgr_fini(drvdata);
	cc_sram_mgr_fini(drvdata);
	cc_fips_fini(drvdata);
	cc_debugfs_fini(drvdata);
	fini_cc_regs(drvdata);
	cc_clk_off(drvdata);
}
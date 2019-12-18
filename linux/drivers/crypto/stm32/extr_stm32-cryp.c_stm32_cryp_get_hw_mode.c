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
typedef  int /*<<< orphan*/  u32 ;
struct stm32_cryp {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_AES_CBC ; 
 int /*<<< orphan*/  CR_AES_CCM ; 
 int /*<<< orphan*/  CR_AES_CTR ; 
 int /*<<< orphan*/  CR_AES_ECB ; 
 int /*<<< orphan*/  CR_AES_GCM ; 
 int /*<<< orphan*/  CR_AES_UNKNOWN ; 
 int /*<<< orphan*/  CR_DES_CBC ; 
 int /*<<< orphan*/  CR_DES_ECB ; 
 int /*<<< orphan*/  CR_TDES_CBC ; 
 int /*<<< orphan*/  CR_TDES_ECB ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_aes (struct stm32_cryp*) ; 
 scalar_t__ is_cbc (struct stm32_cryp*) ; 
 scalar_t__ is_ccm (struct stm32_cryp*) ; 
 scalar_t__ is_ctr (struct stm32_cryp*) ; 
 scalar_t__ is_des (struct stm32_cryp*) ; 
 scalar_t__ is_ecb (struct stm32_cryp*) ; 
 scalar_t__ is_gcm (struct stm32_cryp*) ; 
 scalar_t__ is_tdes (struct stm32_cryp*) ; 

__attribute__((used)) static u32 stm32_cryp_get_hw_mode(struct stm32_cryp *cryp)
{
	if (is_aes(cryp) && is_ecb(cryp))
		return CR_AES_ECB;

	if (is_aes(cryp) && is_cbc(cryp))
		return CR_AES_CBC;

	if (is_aes(cryp) && is_ctr(cryp))
		return CR_AES_CTR;

	if (is_aes(cryp) && is_gcm(cryp))
		return CR_AES_GCM;

	if (is_aes(cryp) && is_ccm(cryp))
		return CR_AES_CCM;

	if (is_des(cryp) && is_ecb(cryp))
		return CR_DES_ECB;

	if (is_des(cryp) && is_cbc(cryp))
		return CR_DES_CBC;

	if (is_tdes(cryp) && is_ecb(cryp))
		return CR_TDES_ECB;

	if (is_tdes(cryp) && is_cbc(cryp))
		return CR_TDES_CBC;

	dev_err(cryp->dev, "Unknown mode\n");
	return CR_AES_UNKNOWN;
}
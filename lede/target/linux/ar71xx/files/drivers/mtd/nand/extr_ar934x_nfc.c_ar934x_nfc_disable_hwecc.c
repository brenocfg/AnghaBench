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
struct ar934x_nfc {int /*<<< orphan*/  ctrl_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR934X_NFC_CTRL_CUSTOM_SIZE_EN ; 
 int /*<<< orphan*/  AR934X_NFC_CTRL_ECC_EN ; 

__attribute__((used)) static inline void
ar934x_nfc_disable_hwecc(struct ar934x_nfc *nfc)
{
	nfc->ctrl_reg &= ~AR934X_NFC_CTRL_ECC_EN;
	nfc->ctrl_reg |= AR934X_NFC_CTRL_CUSTOM_SIZE_EN;
}
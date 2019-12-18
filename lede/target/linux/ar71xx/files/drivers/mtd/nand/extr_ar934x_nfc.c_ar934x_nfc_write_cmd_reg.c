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
struct ar934x_nfc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR934X_NFC_REG_CMD ; 
 int /*<<< orphan*/  ar934x_nfc_rr (struct ar934x_nfc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar934x_nfc_wr (struct ar934x_nfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void ar934x_nfc_write_cmd_reg(struct ar934x_nfc *nfc, u32 cmd_reg)
{
	wmb();

	ar934x_nfc_wr(nfc, AR934X_NFC_REG_CMD, cmd_reg);
	/* flush write */
	ar934x_nfc_rr(nfc, AR934X_NFC_REG_CMD);
}
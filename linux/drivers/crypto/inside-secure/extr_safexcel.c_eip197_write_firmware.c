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
struct safexcel_crypto_priv {scalar_t__ base; } ;
struct firmware {int size; scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ EIP197_CLASSIFICATION_RAMS ; 
 int EIP197_FW_TERMINAL_NOPS ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int eip197_write_firmware(struct safexcel_crypto_priv *priv,
				  const struct firmware *fw)
{
	const u32 *data = (const u32 *)fw->data;
	int i;

	/* Write the firmware */
	for (i = 0; i < fw->size / sizeof(u32); i++)
		writel(be32_to_cpu(data[i]),
		       priv->base + EIP197_CLASSIFICATION_RAMS + i * sizeof(u32));

	/* Exclude final 2 NOPs from size */
	return i - EIP197_FW_TERMINAL_NOPS;
}
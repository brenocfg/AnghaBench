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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  csum ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  CH_ERR (int /*<<< orphan*/ *,char*,int) ; 
 int EINVAL ; 
 scalar_t__ ntohl (int const) ; 

int t3_check_tpsram(adapter_t *adapter, const u8 *tp_sram, unsigned int size)
{
	u32 csum;
	unsigned int i;
	const u32 *p = (const u32 *)tp_sram;

	/* Verify checksum */
	for (csum = 0, i = 0; i < size / sizeof(csum); i++)
		csum += ntohl(p[i]);
	if (csum != 0xffffffff) {
		CH_ERR(adapter, "corrupted protocol SRAM image, checksum %u\n",
		       csum);
		return -EINVAL;
	}

	return 0;
}
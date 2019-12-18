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
typedef  int uint8_t ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int SSD_DESC_BLOCK_ILI ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*) ; 

void
scsi_block_sbuf(struct sbuf *sb, uint8_t block_bits)
{

	sbuf_printf(sb, "Block Command Sense Data: ");
	if (block_bits & SSD_DESC_BLOCK_ILI)
		sbuf_printf(sb, "ILI");
}
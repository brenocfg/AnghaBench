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
typedef  union al_udma_desc {int dummy; } al_udma_desc ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  al_dbg (char*,...) ; 

__attribute__((used)) static void al_dump_tx_desc(union al_udma_desc *tx_desc)
{
	uint32_t *ptr = (uint32_t *)tx_desc;
	al_dbg("eth tx desc:\n");
	al_dbg("0x%08x\n", *(ptr++));
	al_dbg("0x%08x\n", *(ptr++));
	al_dbg("0x%08x\n", *(ptr++));
	al_dbg("0x%08x\n", *(ptr++));
}
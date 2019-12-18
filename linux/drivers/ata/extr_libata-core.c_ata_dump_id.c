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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,...) ; 

__attribute__((used)) static inline void ata_dump_id(const u16 *id)
{
	DPRINTK("49==0x%04x  "
		"53==0x%04x  "
		"63==0x%04x  "
		"64==0x%04x  "
		"75==0x%04x  \n",
		id[49],
		id[53],
		id[63],
		id[64],
		id[75]);
	DPRINTK("80==0x%04x  "
		"81==0x%04x  "
		"82==0x%04x  "
		"83==0x%04x  "
		"84==0x%04x  \n",
		id[80],
		id[81],
		id[82],
		id[83],
		id[84]);
	DPRINTK("88==0x%04x  "
		"93==0x%04x\n",
		id[88],
		id[93]);
}
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

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int _apl_rd_reg (int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_dbg (int,char*,char*,int,int,int) ; 
 int /*<<< orphan*/  pnd2_printk (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int apl_rd_reg(int port, int off, int op, void *data, size_t sz, char *name)
{
	int ret = 0;

	edac_dbg(2, "Read %s port=%x off=%x op=%x\n", name, port, off, op);
	switch (sz) {
	case 8:
		ret = _apl_rd_reg(port, off + 4, op, (u32 *)(data + 4));
		/* fall through */
	case 4:
		ret |= _apl_rd_reg(port, off, op, (u32 *)data);
		pnd2_printk(KERN_DEBUG, "%s=%x%08x ret=%d\n", name,
					sz == 8 ? *((u32 *)(data + 4)) : 0, *((u32 *)data), ret);
		break;
	}

	return ret;
}
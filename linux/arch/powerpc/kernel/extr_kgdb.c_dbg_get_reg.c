#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_4__ {void* evr; } ;
struct TYPE_6__ {TYPE_1__ thread; } ;
struct TYPE_5__ {int offset; char* name; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int DBG_MAX_REG_NUM ; 
 TYPE_3__* current ; 
 TYPE_2__* dbg_reg_def ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *dbg_get_reg(int regno, void *mem, struct pt_regs *regs)
{
	if (regno >= DBG_MAX_REG_NUM || regno < 0)
		return NULL;

	if (regno < 32 || regno >= 64)
		/* First 0 -> 31 gpr registers*/
		/* pc, msr, ls... registers 64 -> 69 */
		memcpy(mem, (void *)regs + dbg_reg_def[regno].offset,
				dbg_reg_def[regno].size);

	if (regno >= 32 && regno < 64) {
		/* FP registers 32 -> 63 */
#if defined(CONFIG_FSL_BOOKE) && defined(CONFIG_SPE)
		if (current)
			memcpy(mem, &current->thread.evr[regno-32],
					dbg_reg_def[regno].size);
#else
		/* fp registers not used by kernel, leave zero */
		memset(mem, 0, dbg_reg_def[regno].size);
#endif
	}

	return dbg_reg_def[regno].name;
}
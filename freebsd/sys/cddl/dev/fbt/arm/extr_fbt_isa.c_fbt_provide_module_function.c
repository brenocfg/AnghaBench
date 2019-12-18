#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {char* name; scalar_t__ value; scalar_t__ size; } ;
typedef  TYPE_1__ linker_symval_t ;
typedef  TYPE_2__* linker_file_t ;
struct TYPE_10__ {char const* fbtp_name; int* fbtp_patchpoint; int fbtp_savedval; int fbtp_symindx; void* fbtp_hashnext; void* fbtp_patchval; int /*<<< orphan*/  fbtp_rval; int /*<<< orphan*/  fbtp_loadcnt; TYPE_2__* fbtp_ctl; void* fbtp_id; struct TYPE_10__* fbtp_probenext; } ;
typedef  TYPE_3__ fbt_probe_t ;
struct TYPE_9__ {int /*<<< orphan*/  fbt_nentries; int /*<<< orphan*/  loadcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_INVOP_B ; 
 int /*<<< orphan*/  DTRACE_INVOP_POPM ; 
 int /*<<< orphan*/  DTRACE_INVOP_PUSHM ; 
 size_t FBT_ADDR2NDX (int*) ; 
 void* FBT_BREAKPOINT ; 
 int /*<<< orphan*/  FBT_ENTRY ; 
 int FBT_JUMP ; 
 int FBT_POPM ; 
 int FBT_PUSHM ; 
 int /*<<< orphan*/  FBT_RETURN ; 
 int FBT_SUBSP ; 
 int LR ; 
 int /*<<< orphan*/  M_FBT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 void* dtrace_probe_create (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 scalar_t__ fbt_excluded (char const*) ; 
 int /*<<< orphan*/  fbt_id ; 
 void** fbt_probetab ; 
 TYPE_3__* malloc (int,int /*<<< orphan*/ ,int) ; 

int
fbt_provide_module_function(linker_file_t lf, int symindx,
    linker_symval_t *symval, void *opaque)
{
	char *modname = opaque;
	const char *name = symval->name;
	fbt_probe_t *fbt, *retfbt;
	uint32_t *instr, *limit;
	int popm;

	if (fbt_excluded(name))
		return (0);

	instr = (uint32_t *)symval->value;
	limit = (uint32_t *)(symval->value + symval->size);

	/*
	 * va_arg functions has first instruction of
	 * sub sp, sp, #?
	 */
	if ((*instr & 0xfffff000) == FBT_SUBSP)
		instr++;

	/*
	 * check if insn is a pushm with LR
	 */
	if ((*instr & 0xffff0000) != FBT_PUSHM ||
	    (*instr & (1 << LR)) == 0)
		return (0);

	fbt = malloc(sizeof (fbt_probe_t), M_FBT, M_WAITOK | M_ZERO);
	fbt->fbtp_name = name;
	fbt->fbtp_id = dtrace_probe_create(fbt_id, modname,
	    name, FBT_ENTRY, 2, fbt);
	fbt->fbtp_patchpoint = instr;
	fbt->fbtp_ctl = lf;
	fbt->fbtp_loadcnt = lf->loadcnt;
	fbt->fbtp_savedval = *instr;
	fbt->fbtp_patchval = FBT_BREAKPOINT;
	fbt->fbtp_rval = DTRACE_INVOP_PUSHM;
	fbt->fbtp_symindx = symindx;

	fbt->fbtp_hashnext = fbt_probetab[FBT_ADDR2NDX(instr)];
	fbt_probetab[FBT_ADDR2NDX(instr)] = fbt;

	lf->fbt_nentries++;

	popm = FBT_POPM | ((*instr) & 0x3FFF) | 0x8000;

	retfbt = NULL;
again:
	for (; instr < limit; instr++) {
		if (*instr == popm)
			break;
		else if ((*instr & 0xff000000) == FBT_JUMP) {
			uint32_t *target, *start;
			int offset;

			offset = (*instr & 0xffffff);
			offset <<= 8;
			offset /= 64;
			target = instr + (2 + offset);
			start = (uint32_t *)symval->value;
			if (target >= limit || target < start)
				break;
		}
	}

	if (instr >= limit)
		return (0);

	/*
	 * We have a winner!
	 */
	fbt = malloc(sizeof (fbt_probe_t), M_FBT, M_WAITOK | M_ZERO);
	fbt->fbtp_name = name;
	if (retfbt == NULL) {
		fbt->fbtp_id = dtrace_probe_create(fbt_id, modname,
		    name, FBT_RETURN, 2, fbt);
	} else {
		retfbt->fbtp_probenext = fbt;
		fbt->fbtp_id = retfbt->fbtp_id;
	}
	retfbt = fbt;

	fbt->fbtp_patchpoint = instr;
	fbt->fbtp_ctl = lf;
	fbt->fbtp_loadcnt = lf->loadcnt;
	fbt->fbtp_symindx = symindx;
	if ((*instr & 0xff000000) == FBT_JUMP)
		fbt->fbtp_rval = DTRACE_INVOP_B;
	else
		fbt->fbtp_rval = DTRACE_INVOP_POPM;
	fbt->fbtp_savedval = *instr;
	fbt->fbtp_patchval = FBT_BREAKPOINT;
	fbt->fbtp_hashnext = fbt_probetab[FBT_ADDR2NDX(instr)];
	fbt_probetab[FBT_ADDR2NDX(instr)] = fbt;

	lf->fbt_nentries++;

	instr++;
	goto again;
}
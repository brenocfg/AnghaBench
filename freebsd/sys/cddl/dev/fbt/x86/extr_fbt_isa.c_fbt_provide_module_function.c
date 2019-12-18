#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_9__ {char* name; int size; scalar_t__ value; } ;
typedef  TYPE_1__ linker_symval_t ;
typedef  TYPE_2__* linker_file_t ;
struct TYPE_11__ {char const* fbtp_name; scalar_t__* fbtp_patchpoint; int fbtp_symindx; uintptr_t fbtp_roffset; struct TYPE_11__* fbtp_hashnext; void* fbtp_patchval; scalar_t__ fbtp_savedval; int /*<<< orphan*/  fbtp_rval; int /*<<< orphan*/  fbtp_loadcnt; TYPE_2__* fbtp_ctl; void* fbtp_id; struct TYPE_11__* fbtp_probenext; struct TYPE_11__* fbtp_tracenext; } ;
typedef  TYPE_3__ fbt_probe_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_10__ {int /*<<< orphan*/  fbt_nentries; int /*<<< orphan*/  loadcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DTRACE_INVOP_LEAVE ; 
 int /*<<< orphan*/  DTRACE_INVOP_POPL_EBP ; 
 int /*<<< orphan*/  DTRACE_INVOP_PUSHL_EBP ; 
 int /*<<< orphan*/  DTRACE_INVOP_RET ; 
 size_t FBT_ADDR2NDX (scalar_t__*) ; 
 int /*<<< orphan*/  FBT_ENTRY ; 
 scalar_t__ FBT_LEAVE ; 
 scalar_t__ FBT_MOVL_ESP_EBP0_V0 ; 
 scalar_t__ FBT_MOVL_ESP_EBP0_V1 ; 
 scalar_t__ FBT_MOVL_ESP_EBP1_V0 ; 
 scalar_t__ FBT_MOVL_ESP_EBP1_V1 ; 
 void* FBT_PATCHVAL ; 
 scalar_t__ FBT_POPL_EBP ; 
 scalar_t__ FBT_PUSHL_EBP ; 
 scalar_t__ FBT_RET ; 
 int /*<<< orphan*/  FBT_RETURN ; 
 scalar_t__ FBT_RET_IMM16 ; 
 int /*<<< orphan*/  M_FBT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int dtrace_instr_size (scalar_t__*) ; 
 void* dtrace_probe_create (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 scalar_t__ fbt_excluded (char const*) ; 
 int /*<<< orphan*/  fbt_id ; 
 TYPE_3__** fbt_probetab ; 
 TYPE_3__* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int
fbt_provide_module_function(linker_file_t lf, int symindx,
    linker_symval_t *symval, void *opaque)
{
	char *modname = opaque;
	const char *name = symval->name;
	fbt_probe_t *fbt, *hash, *retfbt;
	int j;
	int size;
	uint8_t *instr, *limit;

	if (fbt_excluded(name))
		return (0);

	/*
	 * trap_check() is a wrapper for DTrace's fault handler, so we don't
	 * want to be able to instrument it.
	 */
	if (strcmp(name, "trap_check") == 0)
		return (0);

	size = symval->size;

	instr = (uint8_t *) symval->value;
	limit = (uint8_t *) symval->value + symval->size;

#ifdef __amd64__
	while (instr < limit) {
		if (*instr == FBT_PUSHL_EBP)
			break;

		if ((size = dtrace_instr_size(instr)) <= 0)
			break;

		instr += size;
	}

	if (instr >= limit || *instr != FBT_PUSHL_EBP) {
		/*
		 * We either don't save the frame pointer in this
		 * function, or we ran into some disassembly
		 * screw-up.  Either way, we bail.
		 */
		return (0);
	}
#else
	if (instr[0] != FBT_PUSHL_EBP)
		return (0);

	if (!(instr[1] == FBT_MOVL_ESP_EBP0_V0 &&
	    instr[2] == FBT_MOVL_ESP_EBP1_V0) &&
	    !(instr[1] == FBT_MOVL_ESP_EBP0_V1 &&
	    instr[2] == FBT_MOVL_ESP_EBP1_V1))
		return (0);
#endif

	fbt = malloc(sizeof (fbt_probe_t), M_FBT, M_WAITOK | M_ZERO);
	fbt->fbtp_name = name;
	fbt->fbtp_id = dtrace_probe_create(fbt_id, modname,
	    name, FBT_ENTRY, 3, fbt);
	fbt->fbtp_patchpoint = instr;
	fbt->fbtp_ctl = lf;
	fbt->fbtp_loadcnt = lf->loadcnt;
	fbt->fbtp_rval = DTRACE_INVOP_PUSHL_EBP;
	fbt->fbtp_savedval = *instr;
	fbt->fbtp_patchval = FBT_PATCHVAL;
	fbt->fbtp_symindx = symindx;

	for (hash = fbt_probetab[FBT_ADDR2NDX(instr)]; hash != NULL;
	    hash = hash->fbtp_hashnext) {
		if (hash->fbtp_patchpoint == fbt->fbtp_patchpoint) {
			fbt->fbtp_tracenext = hash->fbtp_tracenext;
			hash->fbtp_tracenext = fbt;
			break;
		}
	}
	if (hash == NULL) {
		fbt->fbtp_hashnext = fbt_probetab[FBT_ADDR2NDX(instr)];
		fbt_probetab[FBT_ADDR2NDX(instr)] = fbt;
	}

	lf->fbt_nentries++;

	retfbt = NULL;
again:
	if (instr >= limit)
		return (0);

	/*
	 * If this disassembly fails, then we've likely walked off into
	 * a jump table or some other unsuitable area.  Bail out of the
	 * disassembly now.
	 */
	if ((size = dtrace_instr_size(instr)) <= 0)
		return (0);

#ifdef __amd64__
	/*
	 * We only instrument "ret" on amd64 -- we don't yet instrument
	 * ret imm16, largely because the compiler doesn't seem to
	 * (yet) emit them in the kernel...
	 */
	if (*instr != FBT_RET) {
		instr += size;
		goto again;
	}
#else
	if (!(size == 1 &&
	    (*instr == FBT_POPL_EBP || *instr == FBT_LEAVE) &&
	    (*(instr + 1) == FBT_RET ||
	    *(instr + 1) == FBT_RET_IMM16))) {
		instr += size;
		goto again;
	}
#endif

	/*
	 * We (desperately) want to avoid erroneously instrumenting a
	 * jump table, especially given that our markers are pretty
	 * short:  two bytes on x86, and just one byte on amd64.  To
	 * determine if we're looking at a true instruction sequence
	 * or an inline jump table that happens to contain the same
	 * byte sequences, we resort to some heuristic sleeze:  we
	 * treat this instruction as being contained within a pointer,
	 * and see if that pointer points to within the body of the
	 * function.  If it does, we refuse to instrument it.
	 */
	for (j = 0; j < sizeof (uintptr_t); j++) {
		caddr_t check = (caddr_t) instr - j;
		uint8_t *ptr;

		if (check < symval->value)
			break;

		if (check + sizeof (caddr_t) > (caddr_t)limit)
			continue;

		ptr = *(uint8_t **)check;

		if (ptr >= (uint8_t *) symval->value && ptr < limit) {
			instr += size;
			goto again;
		}
	}

	/*
	 * We have a winner!
	 */
	fbt = malloc(sizeof (fbt_probe_t), M_FBT, M_WAITOK | M_ZERO);
	fbt->fbtp_name = name;

	if (retfbt == NULL) {
		fbt->fbtp_id = dtrace_probe_create(fbt_id, modname,
		    name, FBT_RETURN, 3, fbt);
	} else {
		retfbt->fbtp_probenext = fbt;
		fbt->fbtp_id = retfbt->fbtp_id;
	}

	retfbt = fbt;
	fbt->fbtp_patchpoint = instr;
	fbt->fbtp_ctl = lf;
	fbt->fbtp_loadcnt = lf->loadcnt;
	fbt->fbtp_symindx = symindx;

#ifndef __amd64__
	if (*instr == FBT_POPL_EBP) {
		fbt->fbtp_rval = DTRACE_INVOP_POPL_EBP;
	} else {
		ASSERT(*instr == FBT_LEAVE);
		fbt->fbtp_rval = DTRACE_INVOP_LEAVE;
	}
	fbt->fbtp_roffset =
	    (uintptr_t)(instr - (uint8_t *) symval->value) + 1;

#else
	ASSERT(*instr == FBT_RET);
	fbt->fbtp_rval = DTRACE_INVOP_RET;
	fbt->fbtp_roffset =
	    (uintptr_t)(instr - (uint8_t *) symval->value);
#endif

	fbt->fbtp_savedval = *instr;
	fbt->fbtp_patchval = FBT_PATCHVAL;
	fbt->fbtp_hashnext = fbt_probetab[FBT_ADDR2NDX(instr)];
	fbt_probetab[FBT_ADDR2NDX(instr)] = fbt;

	lf->fbt_nentries++;

	instr += size;
	goto again;
}
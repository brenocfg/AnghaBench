#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uchar_t ;
struct TYPE_10__ {size_t dtds_chunksize; } ;
struct TYPE_11__ {TYPE_2__ dtvs_dynvars; } ;
typedef  TYPE_3__ dtrace_vstate_t ;
struct TYPE_12__ {size_t dttk_size; } ;
typedef  TYPE_4__ dtrace_key_t ;
typedef  int /*<<< orphan*/  dtrace_dynvar_t ;
struct TYPE_9__ {scalar_t__ dtdt_size; } ;
struct TYPE_13__ {size_t dtdv_id; scalar_t__ dtdv_scope; TYPE_1__ dtdv_type; } ;
typedef  TYPE_5__ dtrace_difv_t ;
struct TYPE_14__ {size_t dtdo_len; scalar_t__* dtdo_inttab; size_t dtdo_varlen; TYPE_5__* dtdo_vartab; int /*<<< orphan*/ * dtdo_buf; } ;
typedef  TYPE_6__ dtrace_difo_t ;
typedef  int /*<<< orphan*/  dif_instr_t ;

/* Variables and functions */
 scalar_t__ DIFV_SCOPE_GLOBAL ; 
 scalar_t__ DIFV_SCOPE_THREAD ; 
 size_t DIF_DTR_NREGS ; 
 size_t DIF_INSTR_INTEGER (int /*<<< orphan*/ ) ; 
 int const DIF_INSTR_OP (int /*<<< orphan*/ ) ; 
 size_t DIF_INSTR_R1 (int /*<<< orphan*/ ) ; 
 size_t DIF_INSTR_RD (int /*<<< orphan*/ ) ; 
 size_t DIF_INSTR_VAR (int /*<<< orphan*/ ) ; 
#define  DIF_OP_FLUSHTS 135 
#define  DIF_OP_POPTS 134 
#define  DIF_OP_PUSHTR 133 
#define  DIF_OP_PUSHTV 132 
#define  DIF_OP_SETX 131 
#define  DIF_OP_STGAA 130 
#define  DIF_OP_STTAA 129 
#define  DIF_OP_STTS 128 
 size_t DIF_TYPE_STRING ; 
 scalar_t__ LONG_MAX ; 
 size_t P2ROUNDUP (size_t,int) ; 
 size_t dtrace_strsize_default ; 

__attribute__((used)) static void
dtrace_difo_chunksize(dtrace_difo_t *dp, dtrace_vstate_t *vstate)
{
	uint64_t sval = 0;
	dtrace_key_t tupregs[DIF_DTR_NREGS + 2]; /* +2 for thread and id */
	const dif_instr_t *text = dp->dtdo_buf;
	uint_t pc, srd = 0;
	uint_t ttop = 0;
	size_t size, ksize;
	uint_t id, i;

	for (pc = 0; pc < dp->dtdo_len; pc++) {
		dif_instr_t instr = text[pc];
		uint_t op = DIF_INSTR_OP(instr);
		uint_t rd = DIF_INSTR_RD(instr);
		uint_t r1 = DIF_INSTR_R1(instr);
		uint_t nkeys = 0;
		uchar_t scope = 0;

		dtrace_key_t *key = tupregs;

		switch (op) {
		case DIF_OP_SETX:
			sval = dp->dtdo_inttab[DIF_INSTR_INTEGER(instr)];
			srd = rd;
			continue;

		case DIF_OP_STTS:
			key = &tupregs[DIF_DTR_NREGS];
			key[0].dttk_size = 0;
			key[1].dttk_size = 0;
			nkeys = 2;
			scope = DIFV_SCOPE_THREAD;
			break;

		case DIF_OP_STGAA:
		case DIF_OP_STTAA:
			nkeys = ttop;

			if (DIF_INSTR_OP(instr) == DIF_OP_STTAA)
				key[nkeys++].dttk_size = 0;

			key[nkeys++].dttk_size = 0;

			if (op == DIF_OP_STTAA) {
				scope = DIFV_SCOPE_THREAD;
			} else {
				scope = DIFV_SCOPE_GLOBAL;
			}

			break;

		case DIF_OP_PUSHTR:
			if (ttop == DIF_DTR_NREGS)
				return;

			if ((srd == 0 || sval == 0) && r1 == DIF_TYPE_STRING) {
				/*
				 * If the register for the size of the "pushtr"
				 * is %r0 (or the value is 0) and the type is
				 * a string, we'll use the system-wide default
				 * string size.
				 */
				tupregs[ttop++].dttk_size =
				    dtrace_strsize_default;
			} else {
				if (srd == 0)
					return;

				if (sval > LONG_MAX)
					return;

				tupregs[ttop++].dttk_size = sval;
			}

			break;

		case DIF_OP_PUSHTV:
			if (ttop == DIF_DTR_NREGS)
				return;

			tupregs[ttop++].dttk_size = 0;
			break;

		case DIF_OP_FLUSHTS:
			ttop = 0;
			break;

		case DIF_OP_POPTS:
			if (ttop != 0)
				ttop--;
			break;
		}

		sval = 0;
		srd = 0;

		if (nkeys == 0)
			continue;

		/*
		 * We have a dynamic variable allocation; calculate its size.
		 */
		for (ksize = 0, i = 0; i < nkeys; i++)
			ksize += P2ROUNDUP(key[i].dttk_size, sizeof (uint64_t));

		size = sizeof (dtrace_dynvar_t);
		size += sizeof (dtrace_key_t) * (nkeys - 1);
		size += ksize;

		/*
		 * Now we need to determine the size of the stored data.
		 */
		id = DIF_INSTR_VAR(instr);

		for (i = 0; i < dp->dtdo_varlen; i++) {
			dtrace_difv_t *v = &dp->dtdo_vartab[i];

			if (v->dtdv_id == id && v->dtdv_scope == scope) {
				size += v->dtdv_type.dtdt_size;
				break;
			}
		}

		if (i == dp->dtdo_varlen)
			return;

		/*
		 * We have the size.  If this is larger than the chunk size
		 * for our dynamic variable state, reset the chunk size.
		 */
		size = P2ROUNDUP(size, sizeof (uint64_t));

		/*
		 * Before setting the chunk size, check that we're not going
		 * to set it to a negative value...
		 */
		if (size > LONG_MAX)
			return;

		/*
		 * ...and make certain that we didn't badly overflow.
		 */
		if (size < ksize || size < sizeof (dtrace_dynvar_t))
			return;

		if (size > vstate->dtvs_dynvars.dtds_chunksize)
			vstate->dtvs_dynvars.dtds_chunksize = size;
	}
}
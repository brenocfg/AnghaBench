#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int8_t ;
struct TYPE_17__ {scalar_t__* input; scalar_t__ vid; scalar_t__ offset; } ;
typedef  TYPE_1__ bhnd_sprom_opcode_state ;
typedef  int /*<<< orphan*/  bhnd_nvram_type ;

/* Variables and functions */
#define  BHND_NVRAM_TYPE_CHAR 155 
#define  BHND_NVRAM_TYPE_INT16 154 
#define  BHND_NVRAM_TYPE_INT32 153 
#define  BHND_NVRAM_TYPE_INT64 152 
#define  BHND_NVRAM_TYPE_INT8 151 
#define  BHND_NVRAM_TYPE_STRING 150 
#define  BHND_NVRAM_TYPE_UINT16 149 
#define  BHND_NVRAM_TYPE_UINT32 148 
#define  BHND_NVRAM_TYPE_UINT64 147 
#define  BHND_NVRAM_TYPE_UINT8 146 
 int /*<<< orphan*/  BHND_NV_LOG (char*,...) ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ INT8_MAX ; 
#define  SPROM_OPCODE_DO_BIND 145 
#define  SPROM_OPCODE_DO_BINDN 144 
#define  SPROM_OPCODE_DO_BINDN_IMM 143 
 scalar_t__ SPROM_OPCODE_EOF ; 
 scalar_t__ SPROM_OPCODE_IMM (scalar_t__) ; 
#define  SPROM_OPCODE_MASK 142 
#define  SPROM_OPCODE_MASK_IMM 141 
#define  SPROM_OPCODE_NELEM 140 
#define  SPROM_OPCODE_OFFSET 139 
#define  SPROM_OPCODE_OFFSET_REL_IMM 138 
 scalar_t__ SPROM_OPCODE_OP (scalar_t__) ; 
#define  SPROM_OPCODE_REV_IMM 137 
#define  SPROM_OPCODE_REV_RANGE 136 
#define  SPROM_OPCODE_SHIFT 135 
#define  SPROM_OPCODE_SHIFT_IMM 134 
#define  SPROM_OPCODE_TYPE 133 
#define  SPROM_OPCODE_TYPE_IMM 132 
#define  SPROM_OPCODE_VAR 131 
#define  SPROM_OPCODE_VAR_END 130 
#define  SPROM_OPCODE_VAR_IMM 129 
#define  SPROM_OPCODE_VAR_REL_IMM 128 
 int /*<<< orphan*/  SPROM_OP_BAD (TYPE_1__*,char*,scalar_t__) ; 
 scalar_t__ SPROM_OP_BIND_SKIP_IN_MASK ; 
 scalar_t__ SPROM_OP_BIND_SKIP_IN_SHIFT ; 
 scalar_t__ SPROM_OP_BIND_SKIP_IN_SIGN ; 
 scalar_t__ SPROM_OP_BIND_SKIP_OUT_MASK ; 
 scalar_t__ SPROM_OP_BIND_SKIP_OUT_SHIFT ; 
 scalar_t__ SPROM_OP_DATA_I8 ; 
 scalar_t__ SPROM_OP_DATA_U8 ; 
 scalar_t__ SPROM_OP_REV_END_MASK ; 
 scalar_t__ SPROM_OP_REV_END_SHIFT ; 
 scalar_t__ SPROM_OP_REV_START_MASK ; 
 scalar_t__ SPROM_OP_REV_START_SHIFT ; 
 scalar_t__ UINT32_MAX ; 
 int bhnd_sprom_opcode_apply_scale (TYPE_1__*,scalar_t__*) ; 
 int bhnd_sprom_opcode_end_var (TYPE_1__*) ; 
 int bhnd_sprom_opcode_flush_bind (TYPE_1__*) ; 
 scalar_t__ bhnd_sprom_opcode_matches_layout_rev (TYPE_1__*) ; 
 int bhnd_sprom_opcode_read_opval32 (TYPE_1__*,scalar_t__,scalar_t__*) ; 
 int bhnd_sprom_opcode_rewrite_opcode (TYPE_1__*,scalar_t__*) ; 
 int bhnd_sprom_opcode_set_bind (TYPE_1__*,scalar_t__,scalar_t__,int,scalar_t__) ; 
 int bhnd_sprom_opcode_set_mask (TYPE_1__*,scalar_t__) ; 
 int bhnd_sprom_opcode_set_nelem (TYPE_1__*,scalar_t__) ; 
 int bhnd_sprom_opcode_set_revs (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int bhnd_sprom_opcode_set_shift (TYPE_1__*,scalar_t__) ; 
 int bhnd_sprom_opcode_set_type (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int bhnd_sprom_opcode_set_var (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int
bhnd_sprom_opcode_step(bhnd_sprom_opcode_state *state, uint8_t *opcode)
{
	int error;

	while (*state->input != SPROM_OPCODE_EOF) {
		uint32_t	val;
		uint8_t		op, rewrite, immd;

		/* Fetch opcode */
		*opcode = *state->input;
		op = SPROM_OPCODE_OP(*opcode);
		immd = SPROM_OPCODE_IMM(*opcode);

		/* Clear any existing bind state */
		if ((error = bhnd_sprom_opcode_flush_bind(state)))
			return (error);

		/* Insert local opcode based on current state? */
		rewrite = *opcode;
		if ((error = bhnd_sprom_opcode_rewrite_opcode(state, &rewrite)))
			return (error);

		if (rewrite != *opcode) {
			/* Provide rewritten opcode */
			*opcode = rewrite;

			/* We must keep evaluating until we hit a state
			 * applicable to the SPROM revision we're parsing */
			if (!bhnd_sprom_opcode_matches_layout_rev(state))
				continue;

			return (0);
		}

		/* Advance input */
		state->input++;

		switch (op) {
		case SPROM_OPCODE_VAR_IMM:
			if ((error = bhnd_sprom_opcode_set_var(state, immd)))
				return (error);
			break;

		case SPROM_OPCODE_VAR_REL_IMM:
			error = bhnd_sprom_opcode_set_var(state,
			    state->vid + immd);
			if (error)
				return (error);
			break;

		case SPROM_OPCODE_VAR:
			error = bhnd_sprom_opcode_read_opval32(state, immd,
			    &val);
			if (error)
				return (error);

			if ((error = bhnd_sprom_opcode_set_var(state, val)))
				return (error);

			break;

		case SPROM_OPCODE_VAR_END:
			if ((error = bhnd_sprom_opcode_end_var(state)))
				return (error);
			break;

		case SPROM_OPCODE_NELEM:
			immd = *state->input;
			if ((error = bhnd_sprom_opcode_set_nelem(state, immd)))
				return (error);

			state->input++;
			break;

		case SPROM_OPCODE_DO_BIND:
		case SPROM_OPCODE_DO_BINDN: {
			uint8_t	count, skip_in, skip_out;
			bool	skip_in_negative;

			/* Fetch skip arguments */
			skip_in = (immd & SPROM_OP_BIND_SKIP_IN_MASK) >>
			    SPROM_OP_BIND_SKIP_IN_SHIFT;

			skip_in_negative =
			    ((immd & SPROM_OP_BIND_SKIP_IN_SIGN) != 0);

			skip_out = (immd & SPROM_OP_BIND_SKIP_OUT_MASK) >>
			      SPROM_OP_BIND_SKIP_OUT_SHIFT;

			/* Fetch count argument (if any) */
			if (op == SPROM_OPCODE_DO_BINDN) {
				/* Count is provided as trailing U8 */
				count = *state->input;
				state->input++;
			} else {
				count = 1;
			}

			/* Set BIND state */
			error = bhnd_sprom_opcode_set_bind(state, count,
			    skip_in, skip_in_negative, skip_out);
			if (error)
				return (error);

			break;
		}
		case SPROM_OPCODE_DO_BINDN_IMM: {
			uint8_t	count, skip_in, skip_out;
			bool	skip_in_negative;

			/* Implicit skip_in/skip_out of 1, count encoded as immd
			 * value */
			count = immd;
			skip_in = 1;
			skip_out = 1;
			skip_in_negative = false;

			error = bhnd_sprom_opcode_set_bind(state, count,
			    skip_in, skip_in_negative, skip_out);
			if (error)
				return (error);
			break;
		}

		case SPROM_OPCODE_REV_IMM:
			error = bhnd_sprom_opcode_set_revs(state, immd, immd);
			if (error)
				return (error);
			break;

		case SPROM_OPCODE_REV_RANGE: {
			uint8_t range;
			uint8_t rstart, rend;

			/* Revision range is encoded in next byte, as
			 * { uint8_t start:4, uint8_t end:4 } */
			range = *state->input;
			rstart = (range & SPROM_OP_REV_START_MASK) >>
			    SPROM_OP_REV_START_SHIFT;
			rend = (range & SPROM_OP_REV_END_MASK) >>
			    SPROM_OP_REV_END_SHIFT;

			/* Update revision bitmask */
			error = bhnd_sprom_opcode_set_revs(state, rstart, rend);
			if (error)
				return (error);

			/* Advance input */
			state->input++;
			break;
		}
		case SPROM_OPCODE_MASK_IMM:
			if ((error = bhnd_sprom_opcode_set_mask(state, immd)))
				return (error);
			break;

		case SPROM_OPCODE_MASK:
			error = bhnd_sprom_opcode_read_opval32(state, immd,
			    &val);
			if (error)
				return (error);

			if ((error = bhnd_sprom_opcode_set_mask(state, val)))
				return (error);
			break;

		case SPROM_OPCODE_SHIFT_IMM:
			error = bhnd_sprom_opcode_set_shift(state, immd * 2);
			if (error)
				return (error);
			break;

		case SPROM_OPCODE_SHIFT: {
			int8_t shift;

			if (immd == SPROM_OP_DATA_I8) {
				shift = (int8_t)(*state->input);
			} else if (immd == SPROM_OP_DATA_U8) {
				val = *state->input;
				if (val > INT8_MAX) {
					SPROM_OP_BAD(state, "invalid shift "
					    "value: %#x\n", val);
				}

				shift = val;
			} else {
				SPROM_OP_BAD(state, "unsupported shift data "
				    "type: %#hhx\n", immd);
				return (EINVAL);
			}

			if ((error = bhnd_sprom_opcode_set_shift(state, shift)))
				return (error);

			state->input++;
			break;
		}
		case SPROM_OPCODE_OFFSET_REL_IMM:
			/* Fetch unscaled relative offset */
			val = immd;

			/* Apply scale */
			error = bhnd_sprom_opcode_apply_scale(state, &val);
			if (error)
				return (error);
	
			/* Adding val must not overflow our offset */
			if (UINT32_MAX - state->offset < val) {
				BHND_NV_LOG("offset out of range\n");
				return (EINVAL);
			}

			/* Adjust offset */
			state->offset += val;
			break;
		case SPROM_OPCODE_OFFSET:
			error = bhnd_sprom_opcode_read_opval32(state, immd,
			    &val);
			if (error)
				return (error);

			state->offset = val;
			break;

		case SPROM_OPCODE_TYPE:
			/* Type follows as U8 */
			immd = *state->input;
			state->input++;

			/* fall through */
		case SPROM_OPCODE_TYPE_IMM:
			switch (immd) {
			case BHND_NVRAM_TYPE_UINT8:
			case BHND_NVRAM_TYPE_UINT16:
			case BHND_NVRAM_TYPE_UINT32:
			case BHND_NVRAM_TYPE_UINT64:
			case BHND_NVRAM_TYPE_INT8:
			case BHND_NVRAM_TYPE_INT16:
			case BHND_NVRAM_TYPE_INT32:
			case BHND_NVRAM_TYPE_INT64:
			case BHND_NVRAM_TYPE_CHAR:
			case BHND_NVRAM_TYPE_STRING:
				error = bhnd_sprom_opcode_set_type(state,
				    (bhnd_nvram_type)immd);
				if (error)
					return (error);
				break;
			default:
				BHND_NV_LOG("unrecognized type %#hhx\n", immd);
				return (EINVAL);
			}
			break;

		default:
			BHND_NV_LOG("unrecognized opcode %#hhx\n", *opcode);
			return (EINVAL);
		}

		/* We must keep evaluating until we hit a state applicable to
		 * the SPROM revision we're parsing */
		if (bhnd_sprom_opcode_matches_layout_rev(state))
			return (0);
	}

	/* End of opcode stream */
	return (ENOENT);
}
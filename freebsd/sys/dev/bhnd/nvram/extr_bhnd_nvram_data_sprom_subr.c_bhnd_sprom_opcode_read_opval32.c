#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
struct TYPE_5__ {int* input; } ;
typedef  TYPE_1__ bhnd_sprom_opcode_state ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SPROM_OP_BAD (TYPE_1__*,char*,int) ; 
#define  SPROM_OP_DATA_I8 132 
#define  SPROM_OP_DATA_U16 131 
#define  SPROM_OP_DATA_U32 130 
#define  SPROM_OP_DATA_U8 129 
#define  SPROM_OP_DATA_U8_SCALED 128 
 int bhnd_sprom_opcode_apply_scale (TYPE_1__*,int*) ; 
 int le16dec (int const*) ; 
 int le32dec (int const*) ; 

__attribute__((used)) static int
bhnd_sprom_opcode_read_opval32(bhnd_sprom_opcode_state *state, uint8_t type,
   uint32_t *opval)
{
	const uint8_t	*p;
	int		 error;

	p = state->input;
	switch (type) {
	case SPROM_OP_DATA_I8:
		/* Convert to signed value first, then sign extend */
		*opval = (int32_t)(int8_t)(*p);
		p += 1;
		break;
	case SPROM_OP_DATA_U8:
		*opval = *p;
		p += 1;
		break;
	case SPROM_OP_DATA_U8_SCALED:
		*opval = *p;

		if ((error = bhnd_sprom_opcode_apply_scale(state, opval)))
			return (error);

		p += 1;
		break;
	case SPROM_OP_DATA_U16:
		*opval = le16dec(p);
		p += 2;
		break;
	case SPROM_OP_DATA_U32:
		*opval = le32dec(p);
		p += 4;
		break;
	default:
		SPROM_OP_BAD(state, "unsupported data type: %hhu\n", type);
		return (EINVAL);
	}

	/* Update read address */
	state->input = p;

	return (0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_5__ {int base_type; void* scale; void* mask; } ;
struct TYPE_6__ {scalar_t__ var_state; TYPE_1__ var; } ;
typedef  TYPE_2__ bhnd_sprom_opcode_state ;
typedef  int bhnd_nvram_type ;

/* Variables and functions */
#define  BHND_NVRAM_TYPE_CHAR 135 
#define  BHND_NVRAM_TYPE_INT16 134 
#define  BHND_NVRAM_TYPE_INT32 133 
#define  BHND_NVRAM_TYPE_INT8 132 
#define  BHND_NVRAM_TYPE_STRING 131 
#define  BHND_NVRAM_TYPE_UINT16 130 
#define  BHND_NVRAM_TYPE_UINT32 129 
#define  BHND_NVRAM_TYPE_UINT8 128 
 int EINVAL ; 
 scalar_t__ SPROM_OPCODE_VAR_STATE_OPEN ; 
 int /*<<< orphan*/  SPROM_OP_BAD (TYPE_2__*,char*,...) ; 
 void* UINT16_MAX ; 
 size_t UINT32_MAX ; 
 void* UINT8_MAX ; 
 int bhnd_nvram_base_type (int) ; 
 size_t bhnd_nvram_type_width (int) ; 

__attribute__((used)) static int
bhnd_sprom_opcode_set_type(bhnd_sprom_opcode_state *state, bhnd_nvram_type type)
{
	bhnd_nvram_type	base_type;
	size_t		width;
	uint32_t	mask;

	/* Must have an open variable definition */
	if (state->var_state != SPROM_OPCODE_VAR_STATE_OPEN) {
		SPROM_OP_BAD(state, "type set outside variable definition\n");
		return (EINVAL);
	}

	/* Fetch type width for use as our scale value */
	width = bhnd_nvram_type_width(type);
	if (width == 0) {
		SPROM_OP_BAD(state, "unsupported variable-width type: %d\n",
		    type);
		return (EINVAL);
	} else if (width > UINT32_MAX) {
		SPROM_OP_BAD(state, "invalid type width %zu for type: %d\n",
		    width, type);
		return (EINVAL);
	}

	/* Determine default mask value for the element type */
	base_type = bhnd_nvram_base_type(type);
	switch (base_type) {
	case BHND_NVRAM_TYPE_UINT8:
	case BHND_NVRAM_TYPE_INT8:
	case BHND_NVRAM_TYPE_CHAR:
		mask = UINT8_MAX;
		break;
	case BHND_NVRAM_TYPE_UINT16:
	case BHND_NVRAM_TYPE_INT16:
		mask = UINT16_MAX;
		break;
	case BHND_NVRAM_TYPE_UINT32:
	case BHND_NVRAM_TYPE_INT32:
		mask = UINT32_MAX;
		break;
	case BHND_NVRAM_TYPE_STRING:
		/* fallthrough (unused by SPROM) */
	default:
		SPROM_OP_BAD(state, "unsupported type: %d\n", type);
		return (EINVAL);
	}
	
	/* Update state */
	state->var.base_type = base_type;
	state->var.mask = mask;
	state->var.scale = (uint32_t)width;

	return (0);
}
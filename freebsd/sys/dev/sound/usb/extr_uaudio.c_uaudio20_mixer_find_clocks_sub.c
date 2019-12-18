#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_14__ {TYPE_6__* csrc_v2; TYPE_5__* cmul_v2; TYPE_4__* csel_v2; TYPE_3__* ot_v2; TYPE_2__* it_v2; TYPE_1__* desc; } ;
struct uaudio_terminal_node {TYPE_7__ u; } ;
struct uaudio_search_result {scalar_t__ recurse_level; int is_input; int* bit_output; int* bit_input; } ;
struct TYPE_13__ {size_t bClockId; } ;
struct TYPE_12__ {size_t bCSourceId; } ;
struct TYPE_11__ {size_t* baCSourceId; size_t bNrInPins; } ;
struct TYPE_10__ {size_t bCSourceId; } ;
struct TYPE_9__ {size_t bCSourceId; } ;
struct TYPE_8__ {int bDescriptorSubtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,size_t) ; 
 scalar_t__ UAUDIO_RECURSE_LIMIT ; 
#define  UDESCSUB_AC_CLOCK_MUL 132 
#define  UDESCSUB_AC_CLOCK_SEL 131 
#define  UDESCSUB_AC_CLOCK_SRC 130 
#define  UDESCSUB_AC_INPUT 129 
#define  UDESCSUB_AC_OUTPUT 128 

__attribute__((used)) static void
uaudio20_mixer_find_clocks_sub(struct uaudio_terminal_node *root,
    const uint8_t *p_id, uint8_t n_id,
    struct uaudio_search_result *info)
{
	struct uaudio_terminal_node *iot;
	uint8_t n;
	uint8_t i;
	uint8_t is_last;
	uint8_t id;

top:
	for (n = 0; n < n_id; n++) {

		i = p_id[n];

		if (info->recurse_level == UAUDIO_RECURSE_LIMIT) {
			DPRINTF("avoided going into a circle at id=%d!\n", i);
			return;
		}

		info->recurse_level++;

		iot = (root + i);

		if (iot->u.desc == NULL)
			continue;

		is_last = ((n + 1) == n_id);

		switch (iot->u.desc->bDescriptorSubtype) {
		case UDESCSUB_AC_INPUT:
			info->is_input = 1;
			if (is_last) {
				p_id = &iot->u.it_v2->bCSourceId;
				n_id = 1;
				goto top;
			}
			uaudio20_mixer_find_clocks_sub(root,
			    &iot->u.it_v2->bCSourceId, 1, info);
			break;

		case UDESCSUB_AC_OUTPUT:
			info->is_input = 0;
			if (is_last) {
				p_id = &iot->u.ot_v2->bCSourceId;
				n_id = 1;
				goto top;
			}
			uaudio20_mixer_find_clocks_sub(root,
			    &iot->u.ot_v2->bCSourceId, 1, info);
			break;

		case UDESCSUB_AC_CLOCK_SEL:
			if (is_last) {
				p_id = iot->u.csel_v2->baCSourceId;
				n_id = iot->u.csel_v2->bNrInPins;
				goto top;
			}
			uaudio20_mixer_find_clocks_sub(root,
			    iot->u.csel_v2->baCSourceId,
			    iot->u.csel_v2->bNrInPins, info);
			break;

		case UDESCSUB_AC_CLOCK_MUL:
			if (is_last) {
				p_id = &iot->u.cmul_v2->bCSourceId;
				n_id = 1;
				goto top;
			}
			uaudio20_mixer_find_clocks_sub(root,
			    &iot->u.cmul_v2->bCSourceId,
			    1, info);
			break;

		case UDESCSUB_AC_CLOCK_SRC:

			id = iot->u.csrc_v2->bClockId;

			switch (info->is_input) {
			case 0:
				info->bit_output[id / 8] |= (1 << (id % 8));
				break;
			case 1:
				info->bit_input[id / 8] |= (1 << (id % 8));
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_16__ {TYPE_7__* eu_v1; TYPE_6__* pu_v1; TYPE_5__* su_v1; TYPE_4__* mu_v1; TYPE_3__* ot_v1; TYPE_2__* fu_v1; TYPE_1__* desc; } ;
struct uaudio_terminal_node {TYPE_8__ u; } ;
struct uaudio_search_result {scalar_t__ recurse_level; int* bit_input; } ;
struct TYPE_15__ {size_t* baSourceId; size_t bNrInPins; } ;
struct TYPE_14__ {size_t* baSourceId; size_t bNrInPins; } ;
struct TYPE_13__ {size_t* baSourceId; size_t bNrInPins; } ;
struct TYPE_12__ {size_t* baSourceId; size_t bNrInPins; } ;
struct TYPE_11__ {size_t bSourceId; } ;
struct TYPE_10__ {size_t bSourceId; } ;
struct TYPE_9__ {int bDescriptorSubtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,size_t) ; 
 scalar_t__ UAUDIO_RECURSE_LIMIT ; 
#define  UDESCSUB_AC_EXTENSION 134 
#define  UDESCSUB_AC_FEATURE 133 
#define  UDESCSUB_AC_INPUT 132 
#define  UDESCSUB_AC_MIXER 131 
#define  UDESCSUB_AC_OUTPUT 130 
#define  UDESCSUB_AC_PROCESSING 129 
#define  UDESCSUB_AC_SELECTOR 128 

__attribute__((used)) static void
uaudio_mixer_find_inputs_sub(struct uaudio_terminal_node *root,
    const uint8_t *p_id, uint8_t n_id,
    struct uaudio_search_result *info)
{
	struct uaudio_terminal_node *iot;
	uint8_t n;
	uint8_t i;
	uint8_t is_last;

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
			info->bit_input[i / 8] |= (1 << (i % 8));
			break;

		case UDESCSUB_AC_FEATURE:
			if (is_last) {
				p_id = &iot->u.fu_v1->bSourceId;
				n_id = 1;
				goto top;
			}
			uaudio_mixer_find_inputs_sub(
			    root, &iot->u.fu_v1->bSourceId, 1, info);
			break;

		case UDESCSUB_AC_OUTPUT:
			if (is_last) {
				p_id = &iot->u.ot_v1->bSourceId;
				n_id = 1;
				goto top;
			}
			uaudio_mixer_find_inputs_sub(
			    root, &iot->u.ot_v1->bSourceId, 1, info);
			break;

		case UDESCSUB_AC_MIXER:
			if (is_last) {
				p_id = iot->u.mu_v1->baSourceId;
				n_id = iot->u.mu_v1->bNrInPins;
				goto top;
			}
			uaudio_mixer_find_inputs_sub(
			    root, iot->u.mu_v1->baSourceId,
			    iot->u.mu_v1->bNrInPins, info);
			break;

		case UDESCSUB_AC_SELECTOR:
			if (is_last) {
				p_id = iot->u.su_v1->baSourceId;
				n_id = iot->u.su_v1->bNrInPins;
				goto top;
			}
			uaudio_mixer_find_inputs_sub(
			    root, iot->u.su_v1->baSourceId,
			    iot->u.su_v1->bNrInPins, info);
			break;

		case UDESCSUB_AC_PROCESSING:
			if (is_last) {
				p_id = iot->u.pu_v1->baSourceId;
				n_id = iot->u.pu_v1->bNrInPins;
				goto top;
			}
			uaudio_mixer_find_inputs_sub(
			    root, iot->u.pu_v1->baSourceId,
			    iot->u.pu_v1->bNrInPins, info);
			break;

		case UDESCSUB_AC_EXTENSION:
			if (is_last) {
				p_id = iot->u.eu_v1->baSourceId;
				n_id = iot->u.eu_v1->bNrInPins;
				goto top;
			}
			uaudio_mixer_find_inputs_sub(
			    root, iot->u.eu_v1->baSourceId,
			    iot->u.eu_v1->bNrInPins, info);
			break;

		default:
			break;
		}
	}
}
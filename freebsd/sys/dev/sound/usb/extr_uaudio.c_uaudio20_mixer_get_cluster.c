#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct usb_descriptor {int bDescriptorSubtype; } ;
struct usb_audio20_cluster {int /*<<< orphan*/  iChannelNames; int /*<<< orphan*/ * bmChannelConfig; int /*<<< orphan*/  bNrChannels; } ;
struct TYPE_11__ {TYPE_9__* eu_v2; TYPE_8__* pu_v2; TYPE_7__* fu_v2; TYPE_6__* ef_v2; TYPE_5__* ru_v2; TYPE_4__* su_v2; TYPE_3__* mu_v2; TYPE_2__* ot_v2; TYPE_1__* it_v2; struct usb_descriptor* desc; } ;
struct uaudio_terminal_node {TYPE_10__ u; } ;
typedef  int /*<<< orphan*/  r ;
struct TYPE_20__ {size_t bNrInPins; int /*<<< orphan*/ * baSourceId; } ;
struct TYPE_19__ {size_t bNrInPins; int /*<<< orphan*/ * baSourceId; } ;
struct TYPE_18__ {scalar_t__ bSourceId; } ;
struct TYPE_17__ {scalar_t__ bSourceId; } ;
struct TYPE_16__ {scalar_t__ bSourceId; } ;
struct TYPE_15__ {scalar_t__* baSourceId; int /*<<< orphan*/  bNrInPins; } ;
struct TYPE_14__ {size_t bNrInPins; int /*<<< orphan*/ * baSourceId; } ;
struct TYPE_13__ {scalar_t__ bSourceId; } ;
struct TYPE_12__ {int /*<<< orphan*/  iTerminal; int /*<<< orphan*/ * bmChannelConfig; int /*<<< orphan*/  bNrChannels; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 scalar_t__ UAUDIO_RECURSE_LIMIT ; 
#define  UDESCSUB_AC_EFFECT 136 
#define  UDESCSUB_AC_EXTENSION_V2 135 
#define  UDESCSUB_AC_FEATURE 134 
#define  UDESCSUB_AC_INPUT 133 
#define  UDESCSUB_AC_MIXER 132 
#define  UDESCSUB_AC_OUTPUT 131 
#define  UDESCSUB_AC_PROCESSING_V2 130 
#define  UDESCSUB_AC_SAMPLE_RT 129 
#define  UDESCSUB_AC_SELECTOR 128 
 int /*<<< orphan*/  memset (struct usb_audio20_cluster*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct usb_audio20_cluster
uaudio20_mixer_get_cluster(uint8_t id, const struct uaudio_terminal_node *iot)
{
	struct usb_audio20_cluster r;
	const struct usb_descriptor *dp;
	uint8_t i;

	for (i = 0; i < UAUDIO_RECURSE_LIMIT; i++) {	/* avoid infinite loops */
		dp = iot[id].u.desc;
		if (dp == NULL)
			goto error;

		switch (dp->bDescriptorSubtype) {
		case UDESCSUB_AC_INPUT:
			r.bNrChannels = iot[id].u.it_v2->bNrChannels;
			r.bmChannelConfig[0] = iot[id].u.it_v2->bmChannelConfig[0];
			r.bmChannelConfig[1] = iot[id].u.it_v2->bmChannelConfig[1];
			r.bmChannelConfig[2] = iot[id].u.it_v2->bmChannelConfig[2];
			r.bmChannelConfig[3] = iot[id].u.it_v2->bmChannelConfig[3];
			r.iChannelNames = iot[id].u.it_v2->iTerminal;
			goto done;

		case UDESCSUB_AC_OUTPUT:
			id = iot[id].u.ot_v2->bSourceId;
			break;

		case UDESCSUB_AC_MIXER:
			r = *(const struct usb_audio20_cluster *)
			    &iot[id].u.mu_v2->baSourceId[
			    iot[id].u.mu_v2->bNrInPins];
			goto done;

		case UDESCSUB_AC_SELECTOR:
			if (iot[id].u.su_v2->bNrInPins > 0) {
				/* XXX This is not really right */
				id = iot[id].u.su_v2->baSourceId[0];
			}
			break;

		case UDESCSUB_AC_SAMPLE_RT:
			id = iot[id].u.ru_v2->bSourceId;
			break;

		case UDESCSUB_AC_EFFECT:
			id = iot[id].u.ef_v2->bSourceId;
			break;

		case UDESCSUB_AC_FEATURE:
			id = iot[id].u.fu_v2->bSourceId;
			break;

		case UDESCSUB_AC_PROCESSING_V2:
			r = *((const struct usb_audio20_cluster *)
			    &iot[id].u.pu_v2->baSourceId[
			    iot[id].u.pu_v2->bNrInPins]);
			goto done;

		case UDESCSUB_AC_EXTENSION_V2:
			r = *((const struct usb_audio20_cluster *)
			    &iot[id].u.eu_v2->baSourceId[
			    iot[id].u.eu_v2->bNrInPins]);
			goto done;

		default:
			goto error;
		}
	}
error:
	DPRINTF("Bad data!\n");
	memset(&r, 0, sizeof(r));
done:
	return (r);
}
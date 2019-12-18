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
typedef  scalar_t__ uint8_t ;
struct usb_descriptor {int bDescriptorSubtype; } ;
struct usb_audio_cluster {int /*<<< orphan*/  iChannelNames; int /*<<< orphan*/ * wChannelConfig; int /*<<< orphan*/  bNrChannels; } ;
struct TYPE_16__ {TYPE_7__* eu_v1; TYPE_6__* pu_v1; TYPE_5__* fu_v1; TYPE_4__* su_v1; TYPE_3__* mu_v1; TYPE_2__* ot_v1; TYPE_1__* it_v1; struct usb_descriptor* desc; } ;
struct uaudio_terminal_node {TYPE_8__ u; } ;
typedef  int /*<<< orphan*/  r ;
struct TYPE_15__ {size_t bNrInPins; int /*<<< orphan*/ * baSourceId; } ;
struct TYPE_14__ {size_t bNrInPins; int /*<<< orphan*/ * baSourceId; } ;
struct TYPE_13__ {scalar_t__ bSourceId; } ;
struct TYPE_12__ {scalar_t__* baSourceId; int /*<<< orphan*/  bNrInPins; } ;
struct TYPE_11__ {size_t bNrInPins; int /*<<< orphan*/ * baSourceId; } ;
struct TYPE_10__ {scalar_t__ bSourceId; } ;
struct TYPE_9__ {int /*<<< orphan*/  iChannelNames; int /*<<< orphan*/ * wChannelConfig; int /*<<< orphan*/  bNrChannels; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 scalar_t__ UAUDIO_RECURSE_LIMIT ; 
#define  UDESCSUB_AC_EXTENSION 134 
#define  UDESCSUB_AC_FEATURE 133 
#define  UDESCSUB_AC_INPUT 132 
#define  UDESCSUB_AC_MIXER 131 
#define  UDESCSUB_AC_OUTPUT 130 
#define  UDESCSUB_AC_PROCESSING 129 
#define  UDESCSUB_AC_SELECTOR 128 
 int /*<<< orphan*/  memset (struct usb_audio_cluster*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct usb_audio_cluster
uaudio_mixer_get_cluster(uint8_t id, const struct uaudio_terminal_node *iot)
{
	struct usb_audio_cluster r;
	const struct usb_descriptor *dp;
	uint8_t i;

	for (i = 0; i < UAUDIO_RECURSE_LIMIT; i++) {	/* avoid infinite loops */
		dp = iot[id].u.desc;
		if (dp == NULL) {
			goto error;
		}
		switch (dp->bDescriptorSubtype) {
		case UDESCSUB_AC_INPUT:
			r.bNrChannels = iot[id].u.it_v1->bNrChannels;
			r.wChannelConfig[0] = iot[id].u.it_v1->wChannelConfig[0];
			r.wChannelConfig[1] = iot[id].u.it_v1->wChannelConfig[1];
			r.iChannelNames = iot[id].u.it_v1->iChannelNames;
			goto done;

		case UDESCSUB_AC_OUTPUT:
			id = iot[id].u.ot_v1->bSourceId;
			break;

		case UDESCSUB_AC_MIXER:
			r = *(const struct usb_audio_cluster *)
			    &iot[id].u.mu_v1->baSourceId[
			    iot[id].u.mu_v1->bNrInPins];
			goto done;

		case UDESCSUB_AC_SELECTOR:
			if (iot[id].u.su_v1->bNrInPins > 0) {
				/* XXX This is not really right */
				id = iot[id].u.su_v1->baSourceId[0];
			}
			break;

		case UDESCSUB_AC_FEATURE:
			id = iot[id].u.fu_v1->bSourceId;
			break;

		case UDESCSUB_AC_PROCESSING:
			r = *((const struct usb_audio_cluster *)
			    &iot[id].u.pu_v1->baSourceId[
			    iot[id].u.pu_v1->bNrInPins]);
			goto done;

		case UDESCSUB_AC_EXTENSION:
			r = *((const struct usb_audio_cluster *)
			    &iot[id].u.eu_v1->baSourceId[
			    iot[id].u.eu_v1->bNrInPins]);
			goto done;

		default:
			goto error;
		}
	}
error:
	DPRINTF("bad data\n");
	memset(&r, 0, sizeof(r));
done:
	return (r);
}
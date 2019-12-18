#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/  bEndpointAddress; int /*<<< orphan*/  bmAttributes; } ;
typedef  TYPE_8__ usb_endpoint_descriptor_audio_t ;
union uaudio_sed {int /*<<< orphan*/ * v1; void* v2; int /*<<< orphan*/ * member_0; } ;
union uaudio_asid {TYPE_6__* v1; TYPE_3__* v2; int /*<<< orphan*/ * member_0; } ;
union uaudio_asf1d {TYPE_11__* v1; TYPE_4__* v2; int /*<<< orphan*/ * member_0; } ;
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct usb_midi_streaming_endpoint_descriptor {int bLength; scalar_t__ bDescriptorType; scalar_t__ bDescriptorSubtype; scalar_t__ bNumEmbMIDIJack; } ;
struct usb_interface_descriptor {scalar_t__ bInterfaceNumber; scalar_t__ bInterfaceClass; scalar_t__ bInterfaceSubClass; scalar_t__ bInterfaceProtocol; } ;
struct usb_device {int dummy; } ;
struct usb_descriptor {scalar_t__ bDescriptorType; int bLength; scalar_t__ bDescriptorSubtype; } ;
struct usb_config_descriptor {int dummy; } ;
struct usb_audio_control_descriptor {int /*<<< orphan*/  bcdADC; } ;
struct TYPE_21__ {int* fmtlist; int minspeed; int maxspeed; } ;
struct uaudio_chan {int num_alt; int cur_alt; int* pcm_format; TYPE_7__ pcm_cap; struct uaudio_chan_alt* usb_alt; scalar_t__ set_alt; } ;
struct TYPE_19__ {int* bit_output; int* bit_input; } ;
struct TYPE_16__ {int valid; scalar_t__ max_emb_jack; scalar_t__ iface_alt_index; scalar_t__ iface_index; } ;
struct TYPE_15__ {int flags; scalar_t__ iface_index; } ;
struct uaudio_softc {scalar_t__ sc_uq_au_vendor_class; scalar_t__ sc_mixer_iface_index; int sc_pcm_bitperfect; scalar_t__ sc_sndstat_valid; int /*<<< orphan*/  sc_sndstat; struct uaudio_chan sc_play_chan; struct uaudio_chan sc_rec_chan; int /*<<< orphan*/  sc_mixer_iface_no; TYPE_5__ sc_mixer_clocks; TYPE_2__ sc_midi_chan; int /*<<< orphan*/  sc_udev; TYPE_1__ sc_hid; } ;
struct uaudio_format {int wFormat; scalar_t__ bPrecision; int freebsd_fmt; int /*<<< orphan*/  description; } ;
struct uaudio_chan_alt {int sample_rate; int sample_size; int channels; struct uaudio_format const* p_fmt; int /*<<< orphan*/  usb_cfg; scalar_t__ iface_alt_index; scalar_t__ iface_index; union uaudio_sed p_sed; TYPE_8__* p_ed1; union uaudio_asf1d p_asf1d; } ;
struct TYPE_20__ {int /*<<< orphan*/  wFormatTag; } ;
struct TYPE_18__ {int bSubslotSize; } ;
struct TYPE_17__ {scalar_t__ bNrChannels; int /*<<< orphan*/  bmFormats; } ;
struct TYPE_14__ {scalar_t__ bFormatType; int bSamFreqType; scalar_t__ bNrChannels; int bSubFrameSize; } ;

/* Variables and functions */
 scalar_t__ AS_GENERAL ; 
 int CHAN_MAX_ALT ; 
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 scalar_t__ FORMAT_TYPE ; 
 scalar_t__ FORMAT_TYPE_I ; 
 scalar_t__ MS_GENERAL ; 
 int SND_FORMAT (int,int,int /*<<< orphan*/ ) ; 
 int UAUDIO_HID_VALID ; 
 int UAUDIO_MATRIX_MAX ; 
 int UAUDIO_MAX_CHAN (scalar_t__) ; 
 scalar_t__ UAUDIO_VERSION_20 ; 
 scalar_t__ UAUDIO_VERSION_30 ; 
 int UA_GETSAMP (TYPE_11__*,scalar_t__) ; 
 int UA_SAMP_HI (TYPE_11__*) ; 
 int UA_SAMP_LO (TYPE_11__*) ; 
 scalar_t__ UDESCSUB_AC_HEADER ; 
 scalar_t__ UDESC_CS_ENDPOINT ; 
 scalar_t__ UDESC_CS_INTERFACE ; 
 scalar_t__ UDESC_ENDPOINT ; 
 scalar_t__ UDESC_INTERFACE ; 
 int UEP_MINSIZE ; 
 scalar_t__ UE_DIR_IN ; 
 scalar_t__ UE_DIR_OUT ; 
 scalar_t__ UE_GET_DIR (int /*<<< orphan*/ ) ; 
 scalar_t__ UE_GET_XFERTYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ UE_ISOCHRONOUS ; 
 int UGETDW (int /*<<< orphan*/ ) ; 
 scalar_t__ UGETW (int /*<<< orphan*/ ) ; 
 scalar_t__ UICLASS_AUDIO ; 
 scalar_t__ UICLASS_HID ; 
 scalar_t__ UICLASS_VENDOR ; 
 scalar_t__ UISUBCLASS_AUDIOSTREAM ; 
 scalar_t__ UISUBCLASS_MIDISTREAM ; 
 scalar_t__ USB_SPEED_FULL ; 
 int feeder_matrix_default_format (int) ; 
 int /*<<< orphan*/  sbuf_printf (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,char*,scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 struct uaudio_format* uaudio10_formats ; 
 scalar_t__ uaudio20_check_rate (struct usb_device*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct uaudio_format* uaudio20_formats ; 
 int /*<<< orphan*/  uaudio_cfg_play ; 
 int /*<<< orphan*/  uaudio_cfg_record ; 
 int /*<<< orphan*/  uaudio_chan_dump_ep_desc (TYPE_8__*) ; 
 int /*<<< orphan*/  uaudio_record_fix_fs (TYPE_8__*,int,int) ; 
 struct usb_descriptor* usb_desc_foreach (struct usb_config_descriptor*,struct usb_descriptor*) ; 
 struct usb_config_descriptor* usbd_get_config_descriptor (struct usb_device*) ; 
 int /*<<< orphan*/ * usbd_get_iface (struct usb_device*,scalar_t__) ; 
 scalar_t__ usbd_get_speed (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_set_parent_iface (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
uaudio_chan_fill_info_sub(struct uaudio_softc *sc, struct usb_device *udev,
    uint32_t rate, uint8_t channels, uint8_t bit_resolution)
{
	struct usb_descriptor *desc = NULL;
	union uaudio_asid asid = { NULL };
	union uaudio_asf1d asf1d = { NULL };
	union uaudio_sed sed = { NULL };
	struct usb_midi_streaming_endpoint_descriptor *msid = NULL;
	usb_endpoint_descriptor_audio_t *ed1 = NULL;
	const struct usb_audio_control_descriptor *acdp = NULL;
	struct usb_config_descriptor *cd = usbd_get_config_descriptor(udev);
	struct usb_interface_descriptor *id;
	const struct uaudio_format *p_fmt = NULL;
	struct uaudio_chan *chan;
	struct uaudio_chan_alt *chan_alt;
	uint32_t format;
	uint16_t curidx = 0xFFFF;
	uint16_t lastidx = 0xFFFF;
	uint16_t alt_index = 0;
	uint16_t audio_rev = 0;
	uint16_t x;
	uint8_t ep_dir;
	uint8_t bChannels;
	uint8_t bBitResolution;
	uint8_t audio_if = 0;
	uint8_t midi_if = 0;
	uint8_t uma_if_class;

	while ((desc = usb_desc_foreach(cd, desc))) {

		if ((desc->bDescriptorType == UDESC_INTERFACE) &&
		    (desc->bLength >= sizeof(*id))) {

			id = (void *)desc;

			if (id->bInterfaceNumber != lastidx) {
				lastidx = id->bInterfaceNumber;
				curidx++;
				alt_index = 0;

			} else {
				alt_index++;
			}

			if ((!(sc->sc_hid.flags & UAUDIO_HID_VALID)) &&
			    (id->bInterfaceClass == UICLASS_HID) &&
			    (id->bInterfaceSubClass == 0) &&
			    (id->bInterfaceProtocol == 0) &&
			    (alt_index == 0) &&
			    usbd_get_iface(udev, curidx) != NULL) {
				DPRINTF("Found HID interface at %d\n",
				    curidx);
				sc->sc_hid.flags |= UAUDIO_HID_VALID;
				sc->sc_hid.iface_index = curidx;
			}

			uma_if_class =
			    ((id->bInterfaceClass == UICLASS_AUDIO) ||
			    ((id->bInterfaceClass == UICLASS_VENDOR) &&
			    (sc->sc_uq_au_vendor_class != 0)));

			if ((uma_if_class != 0) &&
			    (id->bInterfaceSubClass == UISUBCLASS_AUDIOSTREAM)) {
				audio_if = 1;
			} else {
				audio_if = 0;
			}

			if ((uma_if_class != 0) &&
			    (id->bInterfaceSubClass == UISUBCLASS_MIDISTREAM)) {

				/*
				 * XXX could allow multiple MIDI interfaces
				 */
				midi_if = 1;

				if ((sc->sc_midi_chan.valid == 0) &&
				    (usbd_get_iface(udev, curidx) != NULL)) {
					sc->sc_midi_chan.iface_index = curidx;
					sc->sc_midi_chan.iface_alt_index = alt_index;
					sc->sc_midi_chan.valid = 1;
				}
			} else {
				midi_if = 0;
			}
			asid.v1 = NULL;
			asf1d.v1 = NULL;
			ed1 = NULL;
			sed.v1 = NULL;

			/*
			 * There can only be one USB audio instance
			 * per USB device. Grab all USB audio
			 * interfaces on this USB device so that we
			 * don't attach USB audio twice:
			 */
			if (alt_index == 0 && curidx != sc->sc_mixer_iface_index &&
			    (id->bInterfaceClass == UICLASS_AUDIO || audio_if != 0 ||
			    midi_if != 0)) {
				usbd_set_parent_iface(sc->sc_udev, curidx,
				    sc->sc_mixer_iface_index);
			}
		}

		if (audio_if == 0) {
			if (midi_if == 0) {
				if ((acdp == NULL) &&
				    (desc->bDescriptorType == UDESC_CS_INTERFACE) &&
				    (desc->bDescriptorSubtype == UDESCSUB_AC_HEADER) &&
				    (desc->bLength >= sizeof(*acdp))) {
					acdp = (void *)desc;
					audio_rev = UGETW(acdp->bcdADC);
				}
			} else {
				msid = (void *)desc;

				/* get the maximum number of embedded jacks in use, if any */
				if (msid->bLength >= sizeof(*msid) &&
				    msid->bDescriptorType == UDESC_CS_ENDPOINT &&
				    msid->bDescriptorSubtype == MS_GENERAL &&
				    msid->bNumEmbMIDIJack > sc->sc_midi_chan.max_emb_jack) {
					sc->sc_midi_chan.max_emb_jack = msid->bNumEmbMIDIJack;
				}
			}
			/*
			 * Don't collect any USB audio descriptors if
			 * this is not an USB audio stream interface.
			 */
			continue;
		}

		if ((acdp != NULL || sc->sc_uq_au_vendor_class != 0) &&
		    (desc->bDescriptorType == UDESC_CS_INTERFACE) &&
		    (desc->bDescriptorSubtype == AS_GENERAL) &&
		    (asid.v1 == NULL)) {
			if (audio_rev >= UAUDIO_VERSION_30) {
				/* FALLTHROUGH */
			} else if (audio_rev >= UAUDIO_VERSION_20) {
				if (desc->bLength >= sizeof(*asid.v2)) {
					asid.v2 = (void *)desc;
				}
			} else {
				if (desc->bLength >= sizeof(*asid.v1)) {
					asid.v1 = (void *)desc;
				}
			}
		}
		if ((acdp != NULL || sc->sc_uq_au_vendor_class != 0) &&
		    (desc->bDescriptorType == UDESC_CS_INTERFACE) &&
		    (desc->bDescriptorSubtype == FORMAT_TYPE) &&
		    (asf1d.v1 == NULL)) {
			if (audio_rev >= UAUDIO_VERSION_30) {
				/* FALLTHROUGH */
			} else if (audio_rev >= UAUDIO_VERSION_20) {
				if (desc->bLength >= sizeof(*asf1d.v2))
					asf1d.v2 = (void *)desc;
			} else {
				if (desc->bLength >= sizeof(*asf1d.v1)) {
					asf1d.v1 = (void *)desc;

					if (asf1d.v1->bFormatType != FORMAT_TYPE_I) {
						DPRINTFN(11, "ignored bFormatType = %d\n",
						    asf1d.v1->bFormatType);
						asf1d.v1 = NULL;
						continue;
					}
					if (desc->bLength < (sizeof(*asf1d.v1) +
					    ((asf1d.v1->bSamFreqType == 0) ? 6 :
					    (asf1d.v1->bSamFreqType * 3)))) {
						DPRINTFN(11, "invalid descriptor, "
						    "too short\n");
						asf1d.v1 = NULL;
						continue;
					}
				}
			}
		}
		if ((desc->bDescriptorType == UDESC_ENDPOINT) &&
		    (desc->bLength >= UEP_MINSIZE) &&
		    (ed1 == NULL)) {
			ed1 = (void *)desc;
			if (UE_GET_XFERTYPE(ed1->bmAttributes) != UE_ISOCHRONOUS) {
				ed1 = NULL;
				continue;
			}
		}
		if ((acdp != NULL || sc->sc_uq_au_vendor_class != 0) &&
		    (desc->bDescriptorType == UDESC_CS_ENDPOINT) &&
		    (desc->bDescriptorSubtype == AS_GENERAL) &&
		    (sed.v1 == NULL)) {
			if (audio_rev >= UAUDIO_VERSION_30) {
				/* FALLTHROUGH */
			} else if (audio_rev >= UAUDIO_VERSION_20) {
				if (desc->bLength >= sizeof(*sed.v2))
					sed.v2 = (void *)desc;
			} else {
				if (desc->bLength >= sizeof(*sed.v1))
					sed.v1 = (void *)desc;
			}
		}
		if (asid.v1 == NULL || asf1d.v1 == NULL ||
		    ed1 == NULL || sed.v1 == NULL) {
			/* need more descriptors */
			continue;
		}

		ep_dir = UE_GET_DIR(ed1->bEndpointAddress);

		/* We ignore sync endpoint information until further. */

		if (audio_rev >= UAUDIO_VERSION_30) {
			goto next_ep;
		} else if (audio_rev >= UAUDIO_VERSION_20) {

			uint32_t dwFormat;

			dwFormat = UGETDW(asid.v2->bmFormats);
			bChannels = asid.v2->bNrChannels;
			bBitResolution = asf1d.v2->bSubslotSize * 8;

			if ((bChannels != channels) ||
			    (bBitResolution != bit_resolution)) {
				DPRINTF("Wrong number of channels\n");
				goto next_ep;
			}

			for (p_fmt = uaudio20_formats;
			    p_fmt->wFormat != 0; p_fmt++) {
				if ((p_fmt->wFormat & dwFormat) &&
				    (p_fmt->bPrecision == bBitResolution))
					break;
			}

			if (p_fmt->wFormat == 0) {
				DPRINTF("Unsupported audio format\n");
				goto next_ep;
			}

			for (x = 0; x != 256; x++) {
				if (ep_dir == UE_DIR_OUT) {
					if (!(sc->sc_mixer_clocks.bit_output[x / 8] &
					    (1 << (x % 8)))) {
						continue;
					}
				} else {
					if (!(sc->sc_mixer_clocks.bit_input[x / 8] &
					    (1 << (x % 8)))) {
						continue;
					}
				}

				DPRINTF("Checking clock ID=%d\n", x);

				if (uaudio20_check_rate(udev,
				    sc->sc_mixer_iface_no, x, rate)) {
					DPRINTF("Unsupported sampling "
					    "rate, id=%d\n", x);
					goto next_ep;
				}
			}
		} else {
			uint16_t wFormat;

			wFormat = UGETW(asid.v1->wFormatTag);
			bChannels = UAUDIO_MAX_CHAN(asf1d.v1->bNrChannels);
			bBitResolution = asf1d.v1->bSubFrameSize * 8;

			if (asf1d.v1->bSamFreqType == 0) {
				DPRINTFN(16, "Sample rate: %d-%dHz\n",
				    UA_SAMP_LO(asf1d.v1),
				    UA_SAMP_HI(asf1d.v1));

				if ((rate >= UA_SAMP_LO(asf1d.v1)) &&
				    (rate <= UA_SAMP_HI(asf1d.v1)))
					goto found_rate;
			} else {

				for (x = 0; x < asf1d.v1->bSamFreqType; x++) {
					DPRINTFN(16, "Sample rate = %dHz\n",
					    UA_GETSAMP(asf1d.v1, x));

					if (rate == UA_GETSAMP(asf1d.v1, x))
						goto found_rate;
				}
			}
			goto next_ep;

	found_rate:
			for (p_fmt = uaudio10_formats;
			    p_fmt->wFormat != 0; p_fmt++) {
				if ((p_fmt->wFormat == wFormat) &&
				    (p_fmt->bPrecision == bBitResolution))
					break;
			}
			if (p_fmt->wFormat == 0) {
				DPRINTF("Unsupported audio format\n");
				goto next_ep;
			}

			if ((bChannels != channels) ||
			    (bBitResolution != bit_resolution)) {
				DPRINTF("Wrong number of channels\n");
				goto next_ep;
			}
		}

		chan = (ep_dir == UE_DIR_IN) ?
		    &sc->sc_rec_chan : &sc->sc_play_chan;

		if (usbd_get_iface(udev, curidx) == NULL) {
			DPRINTF("Interface is not valid\n");
			goto next_ep;
		}
		if (chan->num_alt == CHAN_MAX_ALT) {
			DPRINTF("Too many alternate settings\n");
			goto next_ep;
		}
		chan->set_alt = 0;
		chan->cur_alt = CHAN_MAX_ALT;

		chan_alt = &chan->usb_alt[chan->num_alt++];

#ifdef USB_DEBUG
		uaudio_chan_dump_ep_desc(ed1);
#endif
		DPRINTF("Sample rate = %dHz, channels = %d, "
		    "bits = %d, format = %s\n", rate, channels,
		    bit_resolution, p_fmt->description);

		chan_alt->sample_rate = rate;
		chan_alt->p_asf1d = asf1d;
		chan_alt->p_ed1 = ed1;
		chan_alt->p_fmt = p_fmt;
		chan_alt->p_sed = sed;
		chan_alt->iface_index = curidx;
		chan_alt->iface_alt_index = alt_index;

		if (ep_dir == UE_DIR_IN)
			chan_alt->usb_cfg = uaudio_cfg_record;
		else
			chan_alt->usb_cfg = uaudio_cfg_play;

		chan_alt->sample_size = (UAUDIO_MAX_CHAN(channels) *
		    p_fmt->bPrecision) / 8;
		chan_alt->channels = channels;

		if (ep_dir == UE_DIR_IN &&
		    usbd_get_speed(udev) == USB_SPEED_FULL) {
			uaudio_record_fix_fs(ed1,
			    chan_alt->sample_size * (rate / 1000),
			    chan_alt->sample_size * (rate / 4000));
		}

		/* setup play/record format */

		format = chan_alt->p_fmt->freebsd_fmt;

		/* get default SND_FORMAT() */
		format = SND_FORMAT(format, chan_alt->channels, 0);

		switch (chan_alt->channels) {
		uint32_t temp_fmt;
		case 1:
		case 2:
			/* mono and stereo */
			break;
		default:
			/* surround and more */
			temp_fmt = feeder_matrix_default_format(format);
			/* if multichannel, then format can be zero */
			if (temp_fmt != 0)
				format = temp_fmt;
			break;
		}

		/* check if format is not supported */
		if (format == 0) {
			DPRINTF("The selected audio format is not supported\n");
			chan->num_alt--;
			goto next_ep;
		}
		if (chan->num_alt > 1) {
			/* we only accumulate one format at different sample rates */
			if (chan->pcm_format[0] != format) {
				DPRINTF("Multiple formats is not supported\n");
				chan->num_alt--;
				goto next_ep;
			}
			/* ignore if duplicate sample rate entry */
			if (rate == chan->usb_alt[chan->num_alt - 2].sample_rate) {
				DPRINTF("Duplicate sample rate detected\n");
				chan->num_alt--;
				goto next_ep;
			}
		}
		chan->pcm_cap.fmtlist = chan->pcm_format;
		chan->pcm_cap.fmtlist[0] = format;

		/* check if device needs bitperfect */
		if (chan_alt->channels > UAUDIO_MATRIX_MAX)
			sc->sc_pcm_bitperfect = 1;

		if (rate < chan->pcm_cap.minspeed || chan->pcm_cap.minspeed == 0)
			chan->pcm_cap.minspeed = rate;
		if (rate > chan->pcm_cap.maxspeed || chan->pcm_cap.maxspeed == 0)
			chan->pcm_cap.maxspeed = rate;

		if (sc->sc_sndstat_valid != 0) {
			sbuf_printf(&sc->sc_sndstat, "\n\t"
			    "mode %d.%d:(%s) %dch, %dbit, %s, %dHz",
			    curidx, alt_index,
			    (ep_dir == UE_DIR_IN) ? "input" : "output",
				    channels, p_fmt->bPrecision,
				    p_fmt->description, rate);
		}

	next_ep:
		sed.v1 = NULL;
		ed1 = NULL;
	}
}
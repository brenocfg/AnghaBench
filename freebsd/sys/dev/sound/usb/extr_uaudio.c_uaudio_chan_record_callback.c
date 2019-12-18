#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint32_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct uaudio_chan {scalar_t__ start; scalar_t__ end; int sample_curr; int sample_rem; int intr_frames; int* bytes_per_frame; int frames_per_second; size_t cur_alt; size_t set_alt; int cur; int jitter_curr; int /*<<< orphan*/  pcm_ch; int /*<<< orphan*/  running; TYPE_1__* usb_alt; } ;
struct TYPE_2__ {int sample_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,int,int) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int,int,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int usbd_xfer_frame_len (struct usb_xfer*,int) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int usbd_xfer_max_framelen (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frames (struct usb_xfer*,int) ; 
 struct uaudio_chan* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void
uaudio_chan_record_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct uaudio_chan *ch = usbd_xfer_softc(xfer);
	struct usb_page_cache *pc;
	uint32_t offset0;
	uint32_t mfl;
	int m;
	int n;
	int len;
	int actlen;
	int nframes;
	int expected_bytes;
	int sample_size;

	if (ch->start == ch->end) {
		DPRINTF("no buffer!\n");
		return;
	}

	usbd_xfer_status(xfer, &actlen, NULL, NULL, &nframes);
	mfl = usbd_xfer_max_framelen(xfer);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:

		offset0 = 0;
		pc = usbd_xfer_get_frame(xfer, 0);

		/* try to compute the number of expected bytes */
		ch->sample_curr += (ch->sample_rem * ch->intr_frames);

		/* compute number of expected bytes */
		expected_bytes = (ch->intr_frames * ch->bytes_per_frame[0]) +
		    ((ch->sample_curr / ch->frames_per_second) *
		    (ch->bytes_per_frame[1] - ch->bytes_per_frame[0]));

		/* keep remainder */
		ch->sample_curr %= ch->frames_per_second;

		/* get current sample size */
		sample_size = ch->usb_alt[ch->cur_alt].sample_size;

		for (n = 0; n != nframes; n++) {
			uint32_t offset1 = offset0;

			len = usbd_xfer_frame_len(xfer, n);

			/* make sure we only receive complete samples */
			len = len - (len % sample_size);

			/* subtract bytes received from expected payload */
			expected_bytes -= len;

			/* don't receive data when not ready */
			if (ch->running == 0 || ch->cur_alt != ch->set_alt)
				continue;

			/* fill ring buffer with samples, if any */
			while (len > 0) {

				m = (ch->end - ch->cur);

				if (m > len)
					m = len;

				usbd_copy_out(pc, offset1, ch->cur, m);

				len -= m;
				offset1 += m;
				ch->cur += m;

				if (ch->cur >= ch->end)
					ch->cur = ch->start;
			}

			offset0 += mfl;
		}

		/* update current jitter */
		ch->jitter_curr -= (expected_bytes / sample_size);

		/* don't allow a huge amount of jitter to accumulate */
		nframes = 2 * ch->intr_frames;

		/* range check current jitter */
		if (ch->jitter_curr < -nframes)
			ch->jitter_curr = -nframes;
		else if (ch->jitter_curr > nframes)
			ch->jitter_curr = nframes;

		DPRINTFN(6, "transferred %d bytes, jitter %d samples\n",
		    actlen, ch->jitter_curr);

		if (ch->running != 0)
			chn_intr(ch->pcm_ch);

	case USB_ST_SETUP:
tr_setup:
		nframes = ch->intr_frames;

		usbd_xfer_set_frames(xfer, nframes);
		for (n = 0; n != nframes; n++)
			usbd_xfer_set_frame_len(xfer, n, mfl);

		usbd_transfer_submit(xfer);
		break;

	default:			/* Error */
		if (error != USB_ERR_CANCELLED)
			goto tr_setup;
		break;
	}
}
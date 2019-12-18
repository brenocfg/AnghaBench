#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct uaudio_chan {scalar_t__ num_alt; int /*<<< orphan*/  xfer; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 scalar_t__ UAUDIO_NCHANBUFS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,scalar_t__) ; 

int
uaudio_chan_free(struct uaudio_chan *ch)
{
	if (ch->buf != NULL) {
		free(ch->buf, M_DEVBUF);
		ch->buf = NULL;
	}
	usbd_transfer_unsetup(ch->xfer, UAUDIO_NCHANBUFS + 1);

	ch->num_alt = 0;

	return (0);
}
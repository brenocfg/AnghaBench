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
typedef  int /*<<< orphan*/  uint32_t ;
struct uaudio_softc {scalar_t__ sc_uq_audio_swap_lr; } ;
struct uaudio_chan {struct uaudio_softc* priv_sc; } ;
struct pcmchan_matrix {int dummy; } ;

/* Variables and functions */
 int AFMT_CHANNEL (int /*<<< orphan*/ ) ; 
 struct pcmchan_matrix* feeder_matrix_format_map (int /*<<< orphan*/ ) ; 
 struct pcmchan_matrix uaudio_chan_matrix_swap_2_0 ; 

struct pcmchan_matrix *
uaudio_chan_getmatrix(struct uaudio_chan *ch, uint32_t format)
{
	struct uaudio_softc *sc;

	sc = ch->priv_sc;

	if (sc != NULL && sc->sc_uq_audio_swap_lr != 0 &&
	    AFMT_CHANNEL(format) == 2)
		return (&uaudio_chan_matrix_swap_2_0);

	return (feeder_matrix_format_map(format));
}
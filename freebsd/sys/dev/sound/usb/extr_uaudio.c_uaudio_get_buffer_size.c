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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct uaudio_chan_alt {int sample_size; int sample_rate; } ;
struct uaudio_chan {struct uaudio_chan_alt* usb_alt; } ;

/* Variables and functions */
 int UAUDIO_NFRAMES ; 
 int howmany (int,int) ; 

__attribute__((used)) static uint32_t
uaudio_get_buffer_size(struct uaudio_chan *ch, uint8_t alt)
{
	struct uaudio_chan_alt *chan_alt = &ch->usb_alt[alt];
	/* We use 2 times 8ms of buffer */
	uint32_t buf_size = chan_alt->sample_size *
	    howmany(chan_alt->sample_rate * (UAUDIO_NFRAMES / 8), 1000);
	return (buf_size);
}
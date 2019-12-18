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
struct bcm2835_audio_chinfo {scalar_t__ playback_state; scalar_t__ available_space; int /*<<< orphan*/  starved; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 scalar_t__ PLAYBACK_PLAYING ; 
 scalar_t__ VCHIQ_AUDIO_PACKET_SIZE ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ sndbuf_getready (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
bcm2835_audio_buffer_should_sleep(struct bcm2835_audio_chinfo *ch)
{
	
	if (ch->playback_state != PLAYBACK_PLAYING)
		return (true);

	/* Not enough data */
	if (sndbuf_getready(ch->buffer) < VCHIQ_AUDIO_PACKET_SIZE) {
		printf("starve\n");
		ch->starved++;
		return (true);
	}

	/* Not enough free space */
	if (ch->available_space < VCHIQ_AUDIO_PACKET_SIZE) {
		return (true);
	}

	return (false);
}
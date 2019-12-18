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
struct bcm2835_audio_chinfo {int /*<<< orphan*/  buffer; scalar_t__ unsubmittedptr; int /*<<< orphan*/  available_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCHIQ_AUDIO_BUFFER_SIZE ; 
 int /*<<< orphan*/  sndbuf_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bcm2835_audio_reset_channel(struct bcm2835_audio_chinfo *ch)
{

	ch->available_space = VCHIQ_AUDIO_BUFFER_SIZE;
	ch->unsubmittedptr = 0;
	sndbuf_reset(ch->buffer);
}
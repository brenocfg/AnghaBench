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

/* Variables and functions */
 int /*<<< orphan*/  ASSABET_BCR_NCODEC_RST ; 
 int /*<<< orphan*/  ASSABET_BCR_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSABET_BCR_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adv7171_sleep () ; 
 unsigned int codec_nreset ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void assabet_codec_reset(unsigned mask, int set)
{
	unsigned long flags;
	bool old;

	local_irq_save(flags);
	old = !codec_nreset;
	if (set)
		codec_nreset &= ~mask;
	else
		codec_nreset |= mask;

	if (old != !codec_nreset) {
		if (codec_nreset) {
			ASSABET_BCR_set(ASSABET_BCR_NCODEC_RST);
			adv7171_sleep();
		} else {
			ASSABET_BCR_clear(ASSABET_BCR_NCODEC_RST);
		}
	}
	local_irq_restore(flags);
}
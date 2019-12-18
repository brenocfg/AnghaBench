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
struct agg_rchinfo {int /*<<< orphan*/  stereo; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
#define  PCMTRIG_ABORT 131 
#define  PCMTRIG_EMLDMARD 130 
#define  PCMTRIG_START 129 
#define  PCMTRIG_STOP 128 
 int /*<<< orphan*/  aggch_feed_adc_mono (struct agg_rchinfo*) ; 
 int /*<<< orphan*/  aggch_feed_adc_stereo (struct agg_rchinfo*) ; 
 int /*<<< orphan*/  aggch_start_adc (struct agg_rchinfo*) ; 
 int /*<<< orphan*/  aggch_stop_adc (struct agg_rchinfo*) ; 

__attribute__((used)) static int
aggrch_trigger(kobj_t obj, void *sc, int go)
{
	struct agg_rchinfo *ch = sc;

	switch (go) {
	case PCMTRIG_EMLDMARD:
		if (ch->stereo)
			aggch_feed_adc_stereo(ch);
		else
			aggch_feed_adc_mono(ch);
		break;
	case PCMTRIG_START:
		aggch_start_adc(ch);
		break;
	case PCMTRIG_ABORT:
	case PCMTRIG_STOP:
		aggch_stop_adc(ch);
		break;
	}
	return 0;
}
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
typedef  int u_int8_t ;
typedef  int u_int32_t ;
struct snd_mixer {int dummy; } ;
struct cs4231_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4231_LOCK (struct cs4231_softc*) ; 
 int /*<<< orphan*/  CS4231_UNLOCK (struct cs4231_softc*) ; 
 int CS_IN_DAC ; 
 int CS_IN_LINE ; 
 int CS_IN_MASK ; 
 int CS_IN_MIC ; 
 int /*<<< orphan*/  CS_LEFT_INPUT_CONTROL ; 
 int /*<<< orphan*/  CS_RIGHT_INPUT_CONTROL ; 
#define  SOUND_MASK_CD 130 
#define  SOUND_MASK_LINE 129 
#define  SOUND_MASK_MIC 128 
 int cs4231_read (struct cs4231_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4231_write (struct cs4231_softc*,int /*<<< orphan*/ ,int) ; 
 struct cs4231_softc* mix_getdevinfo (struct snd_mixer*) ; 

__attribute__((used)) static u_int32_t
cs4231_mixer_setrecsrc(struct snd_mixer *m, u_int32_t src)
{
	struct cs4231_softc *sc;
	u_int8_t	v;

	sc = mix_getdevinfo(m);
	switch (src) {
	case SOUND_MASK_LINE:
		v = CS_IN_LINE;
		break;

	case SOUND_MASK_CD:
		v = CS_IN_DAC;
		break;

	case SOUND_MASK_MIC:
	default:
		v = CS_IN_MIC;
		src = SOUND_MASK_MIC;
		break;
	}
	CS4231_LOCK(sc);
	cs4231_write(sc, CS_LEFT_INPUT_CONTROL,
	    (cs4231_read(sc, CS_LEFT_INPUT_CONTROL) & CS_IN_MASK) | v);
	cs4231_write(sc, CS_RIGHT_INPUT_CONTROL,
	    (cs4231_read(sc, CS_RIGHT_INPUT_CONTROL) & CS_IN_MASK) | v);
	CS4231_UNLOCK(sc);

	return (src);
}
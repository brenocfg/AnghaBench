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
 int DENOM_MULT ; 
 int FILLTIME ; 
 int LEGATO ; 
 int NUM_MULT ; 
 int fill ; 
 int /*<<< orphan*/ * pitchtab ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 int /*<<< orphan*/  rest (int) ; 
 int /*<<< orphan*/  tone (int /*<<< orphan*/ ,int) ; 
 int whole ; 

__attribute__((used)) static void
playtone(int pitch, int value, int sustain)
{
	int sound, silence, snum = 1, sdenom = 1;

	/* this weirdness avoids floating-point arithmetic */
	for (; sustain; sustain--) {
		/* See the BUGS section in the man page for discussion */
		snum *= NUM_MULT;
		sdenom *= DENOM_MULT;
	}

	if (value == 0 || sdenom == 0)
		return;

	if (pitch == -1)
		rest(whole * snum / (value * sdenom));
	else {
		sound = (whole * snum) / (value * sdenom)
			- (whole * (FILLTIME - fill)) / (value * FILLTIME);
		silence = whole * (FILLTIME-fill) * snum / (FILLTIME * value * sdenom);

#ifdef DEBUG
		(void) printf("playtone: pitch %d for %d ticks, rest for %d ticks\n",
			pitch, sound, silence);
#endif /* DEBUG */

		tone(pitchtab[pitch], sound);
		if (fill != LEGATO)
			rest(silence);
	}
}
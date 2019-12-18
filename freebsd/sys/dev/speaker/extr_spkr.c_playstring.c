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
 int DFLT_OCTAVE ; 
 int DFLT_TEMPO ; 
 int DFLT_VALUE ; 
 void* FALSE ; 
 int /*<<< orphan*/  GETNUM (char*,int) ; 
 int LEGATO ; 
 int MAX_TEMPO ; 
 int MIN_TEMPO ; 
 int MIN_VALUE ; 
 int NORMAL ; 
 int OCTAVE_NOTES ; 
 int SECS_PER_MIN ; 
 int STACCATO ; 
 void* TRUE ; 
 int WHOLE_NOTE ; 
 int /*<<< orphan*/  abs (int) ; 
 int fill ; 
 int nitems (int /*<<< orphan*/ ) ; 
 int* notetab ; 
 int octave ; 
 void* octprefix ; 
 void* octtrack ; 
 int /*<<< orphan*/  pitchtab ; 
 int /*<<< orphan*/  playtone (int,int,int) ; 
 int /*<<< orphan*/  printf (char*,char,char) ; 
 char toupper (char) ; 
 int value ; 
 int whole ; 

__attribute__((used)) static void
playstring(char *cp, size_t slen)
{
	int pitch, oldfill, lastpitch = OCTAVE_NOTES * DFLT_OCTAVE;

#define GETNUM(cp, v)	for(v=0; isdigit(cp[1]) && slen > 0; ) \
				{v = v * 10 + (*++cp - '0'); slen--;}
	for (; slen--; cp++) {
		int sustain, timeval, tempo;
		char c = toupper(*cp);

#ifdef DEBUG
		(void) printf("playstring: %c (%x)\n", c, c);
#endif /* DEBUG */

		switch (c) {
		case 'A':  
		case 'B': 
		case 'C': 
		case 'D': 
		case 'E': 
		case 'F': 
		case 'G':
			/* compute pitch */
			pitch = notetab[c - 'A'] + octave * OCTAVE_NOTES;

			/* this may be followed by an accidental sign */
			if (cp[1] == '#' || cp[1] == '+') {
				++pitch;
				++cp;
				slen--;
			} else if (cp[1] == '-') {
				--pitch;
				++cp;
				slen--;
			}

			/*
			 * If octave-tracking mode is on, and there has been no octave-
			 * setting prefix, find the version of the current letter note
			 * closest to the last regardless of octave.
			 */
			if (octtrack && !octprefix) {
				if (abs(pitch-lastpitch) > abs(pitch+OCTAVE_NOTES - 
					lastpitch)) {
					++octave;
					pitch += OCTAVE_NOTES;
				}

				if (abs(pitch-lastpitch) > abs((pitch-OCTAVE_NOTES) - 
					lastpitch)) {
					--octave;
					pitch -= OCTAVE_NOTES;
				}
			}
			octprefix = FALSE;
			lastpitch = pitch;

			/* ...which may in turn be followed by an override time value */
			GETNUM(cp, timeval);
			if (timeval <= 0 || timeval > MIN_VALUE)
				timeval = value;

			/* ...and/or sustain dots */
			for (sustain = 0; cp[1] == '.'; cp++) { 
				slen--;
				sustain++;
			}

			/* ...and/or a slur mark */
			oldfill = fill;
			if (cp[1] == '_') {
				fill = LEGATO;
				++cp;
				slen--;
			}

			/* time to emit the actual tone */
			playtone(pitch, timeval, sustain);

			fill = oldfill;
			break;
		case 'O':
			if (cp[1] == 'N' || cp[1] == 'n') {
				octprefix = octtrack = FALSE;
				++cp;
				slen--;
			} else if (cp[1] == 'L' || cp[1] == 'l') {
				octtrack = TRUE;
				++cp;
				slen--;
			} else {
				GETNUM(cp, octave);
				if (octave >= nitems(pitchtab) / OCTAVE_NOTES)
					octave = DFLT_OCTAVE;
				octprefix = TRUE;
			}
			break;
		case '>':
			if (octave < nitems(pitchtab) / OCTAVE_NOTES - 1)
				octave++;
			octprefix = TRUE;
			break;
		case '<':
			if (octave > 0)
				octave--;
			octprefix = TRUE;
			break;
		case 'N':
			GETNUM(cp, pitch);
			for (sustain = 0; cp[1] == '.'; cp++) {
				slen--;
				sustain++;
			}
			oldfill = fill;
			if (cp[1] == '_') {
				fill = LEGATO;
				++cp;
				slen--;
			}
			playtone(pitch - 1, value, sustain);
			fill = oldfill;
			break;
		case 'L':
			GETNUM(cp, value);
			if (value <= 0 || value > MIN_VALUE)
				value = DFLT_VALUE;
			break;
		case 'P':
		case '~':
			/* this may be followed by an override time value */
			GETNUM(cp, timeval);
			if (timeval <= 0 || timeval > MIN_VALUE)
				timeval = value;
			for (sustain = 0; cp[1] == '.'; cp++) {
				slen--;
				sustain++;
			}
			playtone(-1, timeval, sustain);
			break;
		case 'T':
			GETNUM(cp, tempo);
			if (tempo < MIN_TEMPO || tempo > MAX_TEMPO)
				tempo = DFLT_TEMPO;
			whole = (100 * SECS_PER_MIN * WHOLE_NOTE) / tempo;
			break;
		case 'M':
			if (cp[1] == 'N' || cp[1] == 'n') {
				fill = NORMAL;
				++cp;
				slen--;
			} else if (cp[1] == 'L' || cp[1] == 'l') {
				fill = LEGATO;
				++cp;
				slen--;
			} else if (cp[1] == 'S' || cp[1] == 's') {
				fill = STACCATO;
				++cp;
				slen--;
			}
			break;
		}
	}
}
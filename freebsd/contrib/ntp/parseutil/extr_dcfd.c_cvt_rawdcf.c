#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  clocktime_t ;
struct TYPE_2__ {unsigned char* onebits; unsigned char* zerobits; } ;

/* Variables and functions */
 int BITS ; 
 unsigned int CVT_BADFMT ; 
 unsigned int CVT_FAIL ; 
 unsigned int CVT_NONE ; 
 int /*<<< orphan*/  PRINTF (char*,char*) ; 
 unsigned long convert_rawdcf (unsigned char*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__ dcfparam ; 
 int /*<<< orphan*/  dprintf (char*) ; 

__attribute__((used)) static unsigned long
cvt_rawdcf(
	   unsigned char   *buffer,
	   int              size,
	   clocktime_t     *clock_time
	   )
{
	register unsigned char *s = buffer;
	register unsigned char *e = buffer + size;
	register unsigned char *b = dcfparam.onebits;
	register unsigned char *c = dcfparam.zerobits;
	register unsigned rtc = CVT_NONE;
	register unsigned int i, lowmax, highmax, cutoff, span;
#define BITS 9
	unsigned char     histbuf[BITS];
	/*
	 * the input buffer contains characters with runs of consecutive
	 * bits set. These set bits are an indication of the DCF77 pulse
	 * length. We assume that we receive the pulse at 50 Baud. Thus
	 * a 100ms pulse would generate a 4 bit train (20ms per bit and
	 * start bit)
	 * a 200ms pulse would create all zeroes (and probably a frame error)
	 *
	 * The basic idea is that on corret reception we must have two
	 * maxima in the pulse length distribution histogram. (one for
	 * the zero representing pulses and one for the one representing
	 * pulses)
	 * There will always be ones in the datastream, thus we have to see
	 * two maxima.
	 * The best point to cut for a 1/0 decision is the minimum between those
	 * between the maxima. The following code tries to find this cutoff point.
	 */

	/*
	 * clear histogram buffer
	 */
	for (i = 0; i < BITS; i++)
	{
		histbuf[i] = 0;
	}

	cutoff = 0;
	lowmax = 0;

	/*
	 * convert sequences of set bits into bits counts updating
	 * the histogram alongway
	 */
	while (s < e)
	{
		register unsigned int ch = *s ^ 0xFF;
		/*
		 * check integrity and update histogramm
		 */
		if (!((ch+1) & ch) || !*s)
		{
			/*
			 * character ok
			 */
			for (i = 0; ch; i++)
			{
				ch >>= 1;
			}

			*s = i;
			histbuf[i]++;
			cutoff += i;
			lowmax++;
		}
		else
		{
			/*
			 * invalid character (no consecutive bit sequence)
			 */
			dprintf(("parse: cvt_rawdcf: character check for 0x%x@%ld FAILED\n",
				 (u_int)*s, (long)(s - buffer)));
			*s = (unsigned char)~0;
			rtc = CVT_FAIL|CVT_BADFMT;
		}
		s++;
	}

	/*
	 * first cutoff estimate (average bit count - must be between both
	 * maxima)
	 */
	if (lowmax)
	{
		cutoff /= lowmax;
	}
	else
	{
		cutoff = 4;	/* doesn't really matter - it'll fail anyway, but gives error output */
	}

	dprintf(("parse: cvt_rawdcf: average bit count: %d\n", cutoff));

	lowmax = 0;  /* weighted sum */
	highmax = 0; /* bitcount */

	/*
	 * collect weighted sum of lower bits (left of initial guess)
	 */
	dprintf(("parse: cvt_rawdcf: histogram:"));
	for (i = 0; i <= cutoff; i++)
	{
		lowmax  += histbuf[i] * i;
		highmax += histbuf[i];
		dprintf((" %d", histbuf[i]));
	}
	dprintf((" <M>"));

	/*
	 * round up
	 */
	lowmax += highmax / 2;

	/*
	 * calculate lower bit maximum (weighted sum / bit count)
	 *
	 * avoid divide by zero
	 */
	if (highmax)
	{
		lowmax /= highmax;
	}
	else
	{
		lowmax = 0;
	}

	highmax = 0; /* weighted sum of upper bits counts */
	cutoff = 0;  /* bitcount */

	/*
	 * collect weighted sum of lower bits (right of initial guess)
	 */
	for (; i < BITS; i++)
	{
		highmax+=histbuf[i] * i;
		cutoff +=histbuf[i];
		dprintf((" %d", histbuf[i]));
	}
	dprintf(("\n"));

	/*
	 * determine upper maximum (weighted sum / bit count)
	 */
	if (cutoff)
	{
		highmax /= cutoff;
	}
	else
	{
		highmax = BITS-1;
	}

	/*
	 * following now holds:
	 * lowmax <= cutoff(initial guess) <= highmax
	 * best cutoff is the minimum nearest to higher bits
	 */

	/*
	 * find the minimum between lowmax and highmax (detecting
	 * possibly a minimum span)
	 */
	span = cutoff = lowmax;
	for (i = lowmax; i <= highmax; i++)
	{
		if (histbuf[cutoff] > histbuf[i])
		{
			/*
			 * got a new minimum move beginning of minimum (cutoff) and
			 * end of minimum (span) there
			 */
			cutoff = span = i;
		}
		else
		    if (histbuf[cutoff] == histbuf[i])
		    {
			    /*
			     * minimum not better yet - but it spans more than
			     * one bit value - follow it
			     */
			    span = i;
		    }
	}

	/*
	 * cutoff point for 1/0 decision is the middle of the minimum section
	 * in the histogram
	 */
	cutoff = (cutoff + span) / 2;

	dprintf(("parse: cvt_rawdcf: lower maximum %d, higher maximum %d, cutoff %d\n", lowmax, highmax, cutoff));

	/*
	 * convert the bit counts to symbolic 1/0 information for data conversion
	 */
	s = buffer;
	while ((s < e) && *c && *b)
	{
		if (*s == (unsigned char)~0)
		{
			/*
			 * invalid character
			 */
			*s = '?';
		}
		else
		{
			/*
			 * symbolic 1/0 representation
			 */
			*s = (*s >= cutoff) ? *b : *c;
		}
		s++;
		b++;
		c++;
	}

	/*
	 * if everything went well so far return the result of the symbolic
	 * conversion routine else just the accumulated errors
	 */
	if (rtc != CVT_NONE)
	{
		PRINTF("%-30s", "*** BAD DATA");
	}

	return (rtc == CVT_NONE) ? convert_rawdcf(buffer, size, clock_time) : rtc;
}
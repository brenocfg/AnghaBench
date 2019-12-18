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
 int STA_CLOCKERR ; 
 int STA_PPSERROR ; 
 int STA_PPSFREQ ; 
 int STA_PPSJITTER ; 
 int STA_PPSSIGNAL ; 
 int STA_PPSTIME ; 
 int STA_PPSWANDER ; 
 int STA_UNSYNC ; 

__attribute__((used)) static bool
ntp_is_time_error(int tsl)
{

	/*
	 * Status word error decode. If any of these conditions occur,
	 * an error is returned, instead of the status word. Most
	 * applications will care only about the fact the system clock
	 * may not be trusted, not about the details.
	 *
	 * Hardware or software error
	 */
	if ((tsl & (STA_UNSYNC | STA_CLOCKERR)) ||

	/*
	 * PPS signal lost when either time or frequency synchronization
	 * requested
	 */
	    (tsl & (STA_PPSFREQ | STA_PPSTIME) &&
	    !(tsl & STA_PPSSIGNAL)) ||

	/*
	 * PPS jitter exceeded when time synchronization requested
	 */
	    (tsl & STA_PPSTIME && tsl & STA_PPSJITTER) ||

	/*
	 * PPS wander exceeded or calibration error when frequency
	 * synchronization requested
	 */
	    (tsl & STA_PPSFREQ &&
	    tsl & (STA_PPSWANDER | STA_PPSERROR)))
		return (true);

	return (false);
}
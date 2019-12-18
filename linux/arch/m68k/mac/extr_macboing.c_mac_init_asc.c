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
struct TYPE_2__ {int ident; } ;

/* Variables and functions */
#define  MAC_MODEL_C660 137 
#define  MAC_MODEL_IIFX 136 
#define  MAC_MODEL_P475 135 
#define  MAC_MODEL_Q630 134 
#define  MAC_MODEL_Q650 133 
#define  MAC_MODEL_Q700 132 
#define  MAC_MODEL_Q800 131 
#define  MAC_MODEL_Q840 130 
#define  MAC_MODEL_Q900 129 
#define  MAC_MODEL_Q950 128 
 int mac_asc_inited ; 
 void* mac_asc_regs ; 
 int mac_asc_samplespersec ; 
 int* mac_asc_wave_tab ; 
 int /*<<< orphan*/ * mac_av_start_bell ; 
 int /*<<< orphan*/ * mac_quadra_start_bell ; 
 int /*<<< orphan*/ * mac_special_bell ; 
 TYPE_1__* macintosh_config ; 

__attribute__((used)) static void mac_init_asc( void )
{
	int i;

	/*
	 * do some machine specific initialization
	 * BTW:
	 * the NetBSD Quadra patch identifies the Enhanced Apple Sound Chip via
	 *	mac_asc_regs[ 0x800 ] & 0xF0 != 0
	 * this makes no sense here, because we have to set the default sample
	 * rate anyway if we want correct frequencies
	 */
	switch ( macintosh_config->ident )
	{
		case MAC_MODEL_IIFX:
			/*
			 * The IIfx is always special ...
			 */
			mac_asc_regs = ( void* )0x50010000;
			break;
			/*
			 * not sure about how correct this list is
			 * machines with the EASC enhanced apple sound chip
			 */
		case MAC_MODEL_Q630:
		case MAC_MODEL_P475:
			mac_special_bell = mac_quadra_start_bell;
			mac_asc_samplespersec = 22150;
			break;
		case MAC_MODEL_C660:
		case MAC_MODEL_Q840:
			/*
			 * The Quadra 660AV and 840AV use the "Singer" custom ASIC for sound I/O.
			 * It appears to be similar to the "AWACS" custom ASIC in the Power Mac
			 * [678]100.  Because Singer and AWACS may have a similar hardware
			 * interface, this would imply that the code in drivers/sound/dmasound.c
			 * for AWACS could be used as a basis for Singer support.  All we have to
			 * do is figure out how to do DMA on the 660AV/840AV through the PSC and
			 * figure out where the Singer hardware sits in memory. (I'd look in the
			 * vicinity of the AWACS location in a Power Mac [678]100 first, or the
			 * current location of the Apple Sound Chip--ASC--in other Macs.)  The
			 * Power Mac [678]100 info can be found in MkLinux Mach kernel sources.
			 *
			 * Quoted from Apple's Tech Info Library, article number 16405:
			 *   "Among desktop Macintosh computers, only the 660AV, 840AV, and Power
			 *   Macintosh models have 16-bit audio input and output capability
			 *   because of the AT&T DSP3210 hardware circuitry and the 16-bit Singer
			 *   codec circuitry in the AVs.  The Audio Waveform Amplifier and
			 *   Converter (AWAC) chip in the Power Macintosh performs the same
			 *   16-bit I/O functionality.  The PowerBook 500 series computers
			 *   support 16-bit stereo output, but only mono input."
			 *
			 *   Technical Information Library (TIL) article number 16405. 
			 *   http://support.apple.com/kb/TA32601 
			 *
			 * --David Kilzer
			 */
			mac_special_bell = mac_av_start_bell;
			break;
		case MAC_MODEL_Q650:
		case MAC_MODEL_Q700:
		case MAC_MODEL_Q800:
		case MAC_MODEL_Q900:
		case MAC_MODEL_Q950:
			/*
			 * Currently not implemented!
			 */
			mac_special_bell = NULL;
			break;
		default:
			/*
			 * Every switch needs a default
			 */
			mac_special_bell = NULL;
			break;
	}

	/*
	 * init the wave table with a simple triangular wave
	 * A sine wave would sure be nicer here ...
	 */
	for ( i = 0; i < 0x400; i++ )
	{
		mac_asc_wave_tab[ i ] = i / 4;
		mac_asc_wave_tab[ i + 0x400 ] = 0xFF - i / 4;
	}
	mac_asc_inited = 1;
}
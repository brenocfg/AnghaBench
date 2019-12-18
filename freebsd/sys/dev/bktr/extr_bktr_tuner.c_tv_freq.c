#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TUNER {int* pllControl; int* bandAddrs; } ;
typedef  TYPE_3__* bktr_ptr_t ;
struct TYPE_10__ {scalar_t__ afc; int frequency; int radio_mode; } ;
struct TYPE_9__ {int tuner_pllAddr; struct TUNER* tuner; } ;
struct TYPE_11__ {TYPE_2__ tuner; TYPE_1__ card; } ;

/* Variables and functions */
 int FM_RADIO_BAND ; 
 int FM_RADIO_FREQUENCY ; 
 int FREQFACTOR ; 
 int HIGH_BAND ; 
 int LOW_BAND ; 
 int MID_BAND ; 
 int TBL_IF ; 
 scalar_t__ TRUE ; 
 size_t TUNER_MT2032 ; 
 int TV_FREQUENCY ; 
 char* bktr_name (TYPE_3__*) ; 
 int do_afc (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  i2cWrite (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  mt2032_set_tv_freq (TYPE_3__*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 struct TUNER const* tuners ; 

int
tv_freq( bktr_ptr_t bktr, int frequency, int type )
{
	const struct TUNER*	tuner;
	u_char			addr;
	u_char			control;
	u_char			band;
	int			N;
	int			band_select = 0;
#if defined( TEST_TUNER_AFC )
	int			oldFrequency, afcDelta;
#endif

	tuner = bktr->card.tuner;
	if ( tuner == NULL )
		return( -1 );

	if (tuner == &tuners[TUNER_MT2032]) {
		mt2032_set_tv_freq(bktr, frequency);
		return 0;
	}
	if (type == TV_FREQUENCY) {
		/*
		 * select the band based on frequency
		 * XXX FIXME: get the cross-over points from the tuner struct
		 */
		if ( frequency < (160 * FREQFACTOR  ) )
		    band_select = LOW_BAND;
		else if ( frequency < (454 * FREQFACTOR ) )
		    band_select = MID_BAND;
		else
		    band_select = HIGH_BAND;

#if defined( TEST_TUNER_AFC )
		if ( bktr->tuner.afc )
			frequency -= 4;
#endif
		/*
		 * N = 16 * { fRF(pc) + fIF(pc) }
		 * or N = 16* fRF(pc) + 16*fIF(pc) }
		 * where:
		 *  pc is picture carrier, fRF & fIF are in MHz
		 *
		 * fortunatly, frequency is passed in as MHz * 16
		 * and the TBL_IF frequency is also stored in MHz * 16
		 */
		N = frequency + TBL_IF;

		/* set the address of the PLL */
		addr    = bktr->card.tuner_pllAddr;
		control = tuner->pllControl[ band_select ];
		band    = tuner->bandAddrs[ band_select ];

		if(!(band && control))		/* Don't try to set un-	*/
		  return(-1);			/* supported modes.	*/

		if ( frequency > bktr->tuner.frequency ) {
			i2cWrite( bktr, addr, (N>>8) & 0x7f, N & 0xff );
			i2cWrite( bktr, addr, control, band );
	        }
	        else {
			i2cWrite( bktr, addr, control, band );
			i2cWrite( bktr, addr, (N>>8) & 0x7f, N & 0xff );
       		}

#if defined( TUNER_AFC )
		if ( bktr->tuner.afc == TRUE ) {
#if defined( TEST_TUNER_AFC )
			oldFrequency = frequency;
#endif
			if ( (N = do_afc( bktr, addr, N )) < 0 ) {
			    /* AFC failed, restore requested frequency */
			    N = frequency + TBL_IF;
#if defined( TEST_TUNER_AFC )
			    printf("%s: do_afc: failed to lock\n",
				   bktr_name(bktr));
#endif
			    i2cWrite( bktr, addr, (N>>8) & 0x7f, N & 0xff );
			}
			else
			    frequency = N - TBL_IF;
#if defined( TEST_TUNER_AFC )
 printf("%s: do_afc: returned freq %d (%d %% %d)\n", bktr_name(bktr), frequency, frequency / 16, frequency % 16);
			    afcDelta = frequency - oldFrequency;
 printf("%s: changed by: %d clicks (%d mod %d)\n", bktr_name(bktr), afcDelta, afcDelta / 16, afcDelta % 16);
#endif
			}
#endif /* TUNER_AFC */

		bktr->tuner.frequency = frequency;
	}

	if ( type == FM_RADIO_FREQUENCY ) {
		band_select = FM_RADIO_BAND;

		/*
		 * N = { fRF(pc) + fIF(pc) }/step_size
                 * The step size is 50kHz for FM radio.
		 * (eg after 102.35MHz comes 102.40 MHz)
		 * fIF is 10.7 MHz (as detailed in the specs)
		 *
		 * frequency is passed in as MHz * 100
		 *
		 * So, we have N = (frequency/100 + 10.70)  /(50/1000)
		 */
		N = (frequency + 1070)/5;

		/* set the address of the PLL */
		addr    = bktr->card.tuner_pllAddr;
		control = tuner->pllControl[ band_select ];
		band    = tuner->bandAddrs[ band_select ];

		if(!(band && control))		/* Don't try to set un-	*/
		  return(-1);			/* supported modes.	*/
	  
		band |= bktr->tuner.radio_mode; /* tuner.radio_mode is set in
						 * the ioctls RADIO_SETMODE
						 * and RADIO_GETMODE */

		i2cWrite( bktr, addr, control, band );
		i2cWrite( bktr, addr, (N>>8) & 0x7f, N & 0xff );

		bktr->tuner.frequency = (N * 5) - 1070;


	}
 

	return( 0 );
}
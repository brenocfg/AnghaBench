#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  size_t u_char ;
typedef  TYPE_2__* bktr_ptr_t ;
struct TYPE_10__ {int* audiomuxs; int gpio_mux_bits; scalar_t__ msp3400c; } ;
struct TYPE_11__ {int audio_mux_select; scalar_t__ audio_mute_state; scalar_t__ bt848_card; scalar_t__ audio_mux_present; scalar_t__ msp_source_selected; int /*<<< orphan*/  msp_addr; TYPE_1__ card; scalar_t__ reverse_mute; } ;

/* Variables and functions */
#define  AUDIO_EXTERN 132 
#define  AUDIO_INTERN 131 
#define  AUDIO_MUTE 130 
#define  AUDIO_TUNER 129 
#define  AUDIO_UNMUTE 128 
 int /*<<< orphan*/  BKTR_GPIO_DATA ; 
 scalar_t__ CARD_IO_BCTV2 ; 
 scalar_t__ FALSE ; 
 int INL (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTL (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ TRUE ; 
 char* bktr_name (TYPE_2__*) ; 
 int /*<<< orphan*/  msp_autodetect (TYPE_2__*) ; 
 int /*<<< orphan*/  msp_dpl_write (TYPE_2__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int,...) ; 
 int /*<<< orphan*/  set_bctv2_audio (TYPE_2__*) ; 

int
set_audio( bktr_ptr_t bktr, int cmd )
{
	u_long		temp;
	volatile u_char	idx;

#if defined( AUDIOMUX_DISCOVER )
	if ( cmd >= 200 )
		cmd -= 200;
	else
#endif /* AUDIOMUX_DISCOVER */

	/* check for existence of audio MUXes */
	if ( !bktr->card.audiomuxs[ 4 ] )
		return( -1 );

	switch (cmd) {
	case AUDIO_TUNER:
#ifdef BKTR_REVERSEMUTE
		bktr->audio_mux_select = 3;
#else
		bktr->audio_mux_select = 0;
#endif

		if (bktr->reverse_mute ) 
		      bktr->audio_mux_select = 0;
		else	
		    bktr->audio_mux_select = 3;

		break;
	case AUDIO_EXTERN:
		bktr->audio_mux_select = 1;
		break;
	case AUDIO_INTERN:
		bktr->audio_mux_select = 2;
		break;
	case AUDIO_MUTE:
		bktr->audio_mute_state = TRUE;	/* set mute */
		break;
	case AUDIO_UNMUTE:
		bktr->audio_mute_state = FALSE;	/* clear mute */
		break;
	default:
		printf("%s: audio cmd error %02x\n", bktr_name(bktr),
		       cmd);
		return( -1 );
	}


	/* Most cards have a simple audio multiplexer to select the
	 * audio source. The I/O_GV card has a more advanced multiplexer
	 * and requires special handling.
	 */
        if ( bktr->bt848_card == CARD_IO_BCTV2 ) {
                set_bctv2_audio( bktr );
                return( 0 );
	}

	/* Proceed with the simpler audio multiplexer code for the majority
	 * of Bt848 cards.
	 */

	/*
	 * Leave the upper bits of the GPIO port alone in case they control
	 * something like the dbx or teletext chips.  This doesn't guarantee
	 * success, but follows the rule of least astonishment.
	 */

	if ( bktr->audio_mute_state == TRUE ) {
#ifdef BKTR_REVERSEMUTE
		idx = 0;
#else
		idx = 3;
#endif

		if (bktr->reverse_mute )
		  idx  = 3;
		else	
		  idx  = 0;

	}
	else
		idx = bktr->audio_mux_select;


	temp = INL(bktr, BKTR_GPIO_DATA) & ~bktr->card.gpio_mux_bits;
#if defined( AUDIOMUX_DISCOVER )
	OUTL(bktr, BKTR_GPIO_DATA, temp | (cmd & 0xff));
	printf("%s: cmd: %d audio mux %x temp %x \n", bktr_name(bktr),
	  	cmd, bktr->card.audiomuxs[ idx ], temp );
#else
	OUTL(bktr, BKTR_GPIO_DATA, temp | bktr->card.audiomuxs[ idx ]);
#endif /* AUDIOMUX_DISCOVER */



	/* Some new Hauppauge cards do not have an audio mux */
	/* Instead we use the MSP34xx chip to select TV audio, Line-In */
	/* FM Radio and Mute */
	/* Examples of this are the Hauppauge 44xxx MSP34xx models */
	/* It is ok to drive both the mux and the MSP34xx chip. */
	/* If there is no mux, the MSP does the switching of the audio source */
	/* If there is a mux, it does the switching of the audio source */

	if ((bktr->card.msp3400c) && (bktr->audio_mux_present == 0)) {

	  if (bktr->audio_mute_state == TRUE ) {
		 msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0000, 0x0000); /* volume to MUTE */
	  } else {
		 if(bktr->audio_mux_select == 0) { /* TV Tuner */
		    msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0000, 0x7300); /* 0 db volume */
		    if (bktr->msp_source_selected != 0) msp_autodetect(bktr);  /* setup TV audio mode */
		    bktr->msp_source_selected = 0;
		 }
		 if(bktr->audio_mux_select == 1) { /* Line In */
		    msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0000, 0x7300); /* 0 db volume */
		    msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x000d, 0x1900); /* scart prescale */
		    msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0008, 0x0220); /* SCART | STEREO */
		    msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0013, 0x0000); /* DSP In = SC1_IN_L/R */
		    bktr->msp_source_selected = 1;
		 }

		 if(bktr->audio_mux_select == 2) { /* FM Radio */
		    msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0000, 0x7300); /* 0 db volume */
		    msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x000d, 0x1900); /* scart prescale */
		    msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0008, 0x0220); /* SCART | STEREO */
		    msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0013, 0x0200); /* DSP In = SC2_IN_L/R */
		    bktr->msp_source_selected = 2;
		 }
	  }
	}


	return( 0 );
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* bktr_ptr_t ;
struct TYPE_7__ {int msp_use_mono_source; int slow_msp_audio; int /*<<< orphan*/  msp_addr; int /*<<< orphan*/  msp_version_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 char* bktr_name (TYPE_1__*) ; 
 scalar_t__ bootverbose ; 
 int msp_dpl_read (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  msp_dpl_write (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  msp_wake_thread (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 

void msp_autodetect( bktr_ptr_t bktr ) {

#ifdef BKTR_NEW_MSP34XX_DRIVER

  /* Just wake up the (maybe) sleeping thread, it'll do everything for us */
  msp_wake_thread(bktr);

#else
  int auto_detect, loops;
  int stereo;

  /* MSP3430G - countries with mono and DBX stereo */
  if (strncmp("3430G", bktr->msp_version_string, 5) == 0){

    msp_dpl_write(bktr, bktr->msp_addr, 0x10, 0x0030,0x2003);/* Enable Auto format detection */
    msp_dpl_write(bktr, bktr->msp_addr, 0x10, 0x0020,0x0020);/* Standard Select Reg. = BTSC-Stereo*/
    msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x000E,0x2403);/* darned if I know */
    msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0008,0x0320);/* Source select = (St or A) */
					                     /* & Ch. Matrix = St */
    msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0000,0x7300);/* Set volume to 0db gain */
  }


  /* MSP3415D SPECIAL CASE Use the Tuner's Mono audio output for the MSP */
  /* (for Hauppauge 44xxx card with Tuner Type 0x2a) */
  else if (  ( (strncmp("3415D", bktr->msp_version_string, 5) == 0)
               &&(bktr->msp_use_mono_source == 1)
              )
           || (bktr->slow_msp_audio == 2) ){
    msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0000, 0x7300); /* 0 db volume */
    msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x000d, 0x1900); /* scart prescale */
    msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0008, 0x0220); /* SCART | STEREO */
    msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0013, 0x0100); /* DSP In = MONO IN */
  }


  /* MSP3410/MSP3415 - countries with mono, stereo using 2 FM channels and NICAM */
  /* FAST sound scheme */
  else if (bktr->slow_msp_audio == 0) {
    msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0000,0x7300);/* Set volume to 0db gain */
    msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0008,0x0000);/* Spkr Source = default(FM/AM) */
    msp_dpl_write(bktr, bktr->msp_addr, 0x10, 0x0020,0x0001);/* Enable Auto format detection */
    msp_dpl_write(bktr, bktr->msp_addr, 0x10, 0x0021,0x0001);/* Auto selection of NICAM/MONO mode */
  }


  /* MSP3410/MSP3415 - European Countries where the fast MSP3410/3415 programming fails */
  /* SLOW sound scheme */
  else if ( bktr->slow_msp_audio == 1) {
    msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0000,0x7300);/* Set volume to 0db gain */
    msp_dpl_write(bktr, bktr->msp_addr, 0x10, 0x0020,0x0001);/* Enable Auto format detection */
    
    /* wait for 0.5s max for terrestrial sound autodetection */
    loops = 10;
    do {
      DELAY(100000);
      auto_detect = msp_dpl_read(bktr, bktr->msp_addr, 0x10, 0x007e);
      loops++;
    } while (auto_detect > 0xff && loops < 50);
    if (bootverbose)printf ("%s: Result of autodetect after %dms: %d\n",
			    bktr_name(bktr), loops*10, auto_detect);

    /* Now set the audio baseband processing */
    switch (auto_detect) {
    case 0:                    /* no TV sound standard detected */
      break;
    case 2:                    /* M Dual FM */
      break;
    case 3:                    /* B/G Dual FM; German stereo */
      /* Read the stereo detection value from DSP reg 0x0018 */
      DELAY(20000);
      stereo = msp_dpl_read(bktr, bktr->msp_addr, 0x12, 0x0018);
      if (bootverbose)printf ("%s: Stereo reg 0x18 a: %d\n",
			      bktr_name(bktr), stereo);
      DELAY(20000);
      stereo = msp_dpl_read(bktr, bktr->msp_addr, 0x12, 0x0018);
      if (bootverbose)printf ("%s: Stereo reg 0x18 b: %d\n",
			      bktr_name(bktr), stereo); 
      DELAY(20000); 
      stereo = msp_dpl_read(bktr, bktr->msp_addr, 0x12, 0x0018);
      if (bootverbose)printf ("%s: Stereo reg 0x18 c: %d\n",
			      bktr_name(bktr), stereo);
      if (stereo > 0x0100 && stereo < 0x8000) { /* Seems to be stereo */
        msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0008,0x0020);/* Loudspeaker set stereo*/
        /*
          set spatial effect strength to 50% enlargement
          set spatial effect mode b, stereo basewidth enlargement only
        */
        msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0005,0x3f28);
      } else if (stereo > 0x8000) {    /* bilingual mode */
        if (bootverbose) printf ("%s: Bilingual mode detected\n",
				 bktr_name(bktr));
        msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0008,0x0000);/* Loudspeaker */
        msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0005,0x0000);/* all spatial effects off */
       } else {                 /* must be mono */
        msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0008,0x0030);/* Loudspeaker */
        /*
          set spatial effect strength to 50% enlargement
          set spatial effect mode a, stereo basewidth enlargement
          and pseudo stereo effect with automatic high-pass filter
        */
        msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0005,0x3f08);
      }
#if 0
       /* The reset value for Channel matrix mode is FM/AM and SOUNDA/LEFT */
       /* We would like STEREO instead val: 0x0020 */
       msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0008,0x0020);/* Loudspeaker */
       msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0009,0x0020);/* Headphone */
       msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x000a,0x0020);/* SCART1 */
       msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0041,0x0020);/* SCART2 */
       msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x000b,0x0020);/* I2S */
       msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x000c,0x0020);/* Quasi-Peak Detector Source */
       msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x000e,0x0001);
#endif
      break;
    case 8:                    /* B/G FM NICAM */
       msp_dpl_write(bktr, bktr->msp_addr, 0x10, 0x0021,0x0001);/* Auto selection of NICAM/MONO mode */
       break;
     case 9:                    /* L_AM NICAM or D/K*/
     case 10:                   /* i-FM NICAM */
       break;
     default:
       if (bootverbose) printf ("%s: Unknown autodetection result value: %d\n",
				bktr_name(bktr), auto_detect); 
     }

  }


  /* uncomment the following line to enable the MSP34xx 1Khz Tone Generator */
  /* turn your speaker volume down low before trying this */
  /* msp_dpl_write(bktr, bktr->msp_addr, 0x12, 0x0014, 0x7f40); */

#endif /* BKTR_NEW_MSP34XX_DRIVER */
}
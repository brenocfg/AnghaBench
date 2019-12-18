#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UWORD ;
typedef  int UBYTE ;
struct TYPE_11__ {int restart; int soundLength; int envInitialValue; int envMode; int envNbStep; int polyCounterFreq; int polyCounterStep; int polyCounterDiv; int counter_ConsSel; } ;
struct TYPE_10__ {int global_On_Off; int Vin_SO1; int Vin_SO2; int SO1_OutputLevel; int SO2_OutputLevel; int Sound1_To_SO1; int Sound1_To_SO2; int Sound1_On_Off; int Sound2_To_SO1; int Sound2_To_SO2; int Sound2_On_Off; int Sound3_To_SO1; int Sound3_To_SO2; int Sound3_On_Off; int Sound4_To_SO1; int Sound4_To_SO2; int Sound4_On_Off; } ;
struct TYPE_9__ {int restart; int on_Off; int soundLength; int selOutputLevel; int frequencyHigh; int frequencyLow; int counter_ConsSel; } ;
struct TYPE_8__ {int restart; int patternDuty; int soundLength; int envInitialValue; int envMode; int envNbStep; int frequencyHigh; int frequencyLow; int counter_ConsSel; } ;
struct TYPE_7__ {int restart; int sweepTime; int sweepMode; int sweepShifts; int patternDuty; int soundLength; int envInitialValue; int envMode; int envNbSweep; int frequencyHigh; int frequencyLow; int counter_ConsSel; } ;
struct TYPE_12__ {TYPE_5__ mode4; TYPE_4__ control; TYPE_3__ mode3; TYPE_2__ mode2; TYPE_1__ mode1; } ;

/* Variables and functions */
#define  FREQUENCY 129 
 int NR10_REG ; 
 int NR11_REG ; 
 int NR12_REG ; 
 int NR13_REG ; 
 int NR14_REG ; 
 int NR21_REG ; 
 int NR22_REG ; 
 int NR23_REG ; 
 int NR24_REG ; 
 int NR30_REG ; 
 int NR31_REG ; 
 int NR32_REG ; 
 int NR33_REG ; 
 int NR34_REG ; 
 int NR41_REG ; 
 int NR42_REG ; 
 int NR43_REG ; 
 int NR44_REG ; 
 int NR50_REG ; 
 int NR51_REG ; 
 int NR52_REG ; 
#define  PLAY 128 
 int current_value (int,int const) ; 
 TYPE_6__* soundReg ; 

void update_value(UBYTE mode, UBYTE line, UWORD value)
{
  if(mode == 0) {
    switch(line)
      {
      case 0: /* global_On_Off */
	soundReg->control.global_On_Off = value;
	NR52_REG = ((UBYTE *)soundReg)[0x16];
	break;
      case 1: /* Vin_SO1 */
	soundReg->control.Vin_SO1 = value;
	NR50_REG = ((UBYTE *)soundReg)[0x14];
	break;
      case 2: /* Vin_SO2 */
	soundReg->control.Vin_SO2 = value;
	NR50_REG = ((UBYTE *)soundReg)[0x14];
	break;
      case 3: /* SO1_OutputLevel */
	soundReg->control.SO1_OutputLevel = value;
	NR50_REG = ((UBYTE *)soundReg)[0x14];
	break;
      case 4: /* SO2_OutputLevel */
	soundReg->control.SO2_OutputLevel = value;
	NR50_REG = ((UBYTE *)soundReg)[0x14];
	break;
      case FREQUENCY:
	update_value(1, FREQUENCY, value);
	update_value(2, FREQUENCY, value);
	update_value(3, FREQUENCY, value);
	break;
      case PLAY: /* restart */
	update_value(1, FREQUENCY, current_value(1, FREQUENCY));
	update_value(2, FREQUENCY, current_value(2, FREQUENCY));
	update_value(3, FREQUENCY, current_value(3, FREQUENCY));
	soundReg->mode1.restart = value;
	soundReg->mode2.restart = value;
	soundReg->mode3.restart = value;
	soundReg->mode4.restart = value;
	NR14_REG = ((UBYTE *)soundReg)[0x04];
	NR24_REG = ((UBYTE *)soundReg)[0x09];
	NR34_REG = ((UBYTE *)soundReg)[0x0E];
	NR44_REG = ((UBYTE *)soundReg)[0x13];
	soundReg->mode1.restart = 0;
	soundReg->mode2.restart = 0;
	soundReg->mode3.restart = 0;
	soundReg->mode4.restart = 0;
	break;
      }
  } else if(mode == 1) {
    switch(line)
      {
      case 0: /* sweepTime */
	soundReg->mode1.sweepTime = value;
	NR10_REG = ((UBYTE *)soundReg)[0x00];
	break;
      case 1: /* sweepMode */
	soundReg->mode1.sweepMode = value;
	NR10_REG = ((UBYTE *)soundReg)[0x00];
	break;
      case 2: /* sweepShifts */
	soundReg->mode1.sweepShifts = value;
	NR10_REG = ((UBYTE *)soundReg)[0x00];
	break;
      case 3: /* patternDuty */
	soundReg->mode1.patternDuty = value;
	NR11_REG = ((UBYTE *)soundReg)[0x01];
	break;
      case 4: /* soundLength */
	soundReg->mode1.soundLength = value;
	NR11_REG = ((UBYTE *)soundReg)[0x01];
	break;
      case 5: /* envInitialValue */
	soundReg->mode1.envInitialValue = value;
	NR12_REG = ((UBYTE *)soundReg)[0x02];
	break;
      case 6: /* envMode */
	soundReg->mode1.envMode = value;
	NR12_REG = ((UBYTE *)soundReg)[0x02];
	break;
      case 7: /* envNbSweep */
	soundReg->mode1.envNbSweep = value;
	NR12_REG = ((UBYTE *)soundReg)[0x02];
	break;
      case 8: /* frequency */
      case FREQUENCY:
	soundReg->mode1.frequencyHigh = value >> 8;
	soundReg->mode1.frequencyLow  = value;
	NR13_REG = ((UBYTE *)soundReg)[0x03];
	NR14_REG = ((UBYTE *)soundReg)[0x04];
	break;
      case 9: /* counter_ConsSel */
	soundReg->mode1.counter_ConsSel = value;
	NR14_REG = ((UBYTE *)soundReg)[0x04];
	break;
      case 10: /* Sound1_To_SO1 */
	soundReg->control.Sound1_To_SO1 = value;
	NR51_REG = ((UBYTE *)soundReg)[0x15];
	break;
      case 11: /* Sound1_To_SO2 */
	soundReg->control.Sound1_To_SO2 = value;
	NR51_REG = ((UBYTE *)soundReg)[0x15];
	break;
      case 12: /* Sound1_On_Off */
	soundReg->control.Sound1_On_Off = value;
	NR52_REG = ((UBYTE *)soundReg)[0x16];
	break;
      case PLAY: /* restart */
	update_value(mode, FREQUENCY, current_value(mode, FREQUENCY));
	soundReg->mode1.restart = value;
	NR14_REG = ((UBYTE *)soundReg)[0x04];
	soundReg->mode1.restart = 0;
	break;
      }
  } else if(mode == 2) {
    switch(line)
      {
      case 0: /* patternDuty */
	soundReg->mode2.patternDuty = value;
	NR21_REG = ((UBYTE *)soundReg)[0x06];
	break;
      case 1: /* soundLength */
	soundReg->mode2.soundLength = value;
	NR21_REG = ((UBYTE *)soundReg)[0x06];
	break;
      case 2: /* envInitialValue */
	soundReg->mode2.envInitialValue = value;
	NR22_REG = ((UBYTE *)soundReg)[0x07];
	break;
      case 3: /* envMode */
	soundReg->mode2.envMode = value;
	NR22_REG = ((UBYTE *)soundReg)[0x07];
	break;
      case 4: /* envNbStep */
	soundReg->mode2.envNbStep = value;
	NR22_REG = ((UBYTE *)soundReg)[0x07];
	break;
      case 5: /* frequency */
      case FREQUENCY:
	soundReg->mode2.frequencyHigh = value >> 8;
	soundReg->mode2.frequencyLow  = value;
	NR23_REG = ((UBYTE *)soundReg)[0x08];
	NR24_REG = ((UBYTE *)soundReg)[0x09];
	break;
      case 6: /* counter_ConsSel */
	soundReg->mode2.counter_ConsSel = value;
	NR24_REG = ((UBYTE *)soundReg)[0x09];
	break;
      case 7: /* Sound2_To_SO1 */
	soundReg->control.Sound2_To_SO1 = value;
	NR51_REG = ((UBYTE *)soundReg)[0x15];
	break;
      case 8: /* Sound2_To_SO2 */
	soundReg->control.Sound2_To_SO2 = value;
	NR51_REG = ((UBYTE *)soundReg)[0x15];
	break;
      case 9: /* Sound2_On_Off */
	soundReg->control.Sound2_On_Off = value;
	NR52_REG = ((UBYTE *)soundReg)[0x16];
	break;
      case PLAY: /* restart */
	update_value(mode, FREQUENCY, current_value(mode, FREQUENCY));
	soundReg->mode2.restart = value;
	NR24_REG = ((UBYTE *)soundReg)[0x09];
	soundReg->mode2.restart = 0;
	break;
      }
  } else if(mode == 3) {
    switch(line)
      {
      case 0: /* on_Off */
	soundReg->mode3.on_Off = value;
	NR30_REG = ((UBYTE *)soundReg)[0x0A];
	break;
      case 1: /* soundLength */
	soundReg->mode3.soundLength = value;
	NR31_REG = ((UBYTE *)soundReg)[0x0B];
	break;
      case 2: /* selOutputLevel */
	soundReg->mode3.selOutputLevel = value;
	NR32_REG = ((UBYTE *)soundReg)[0x0C];
	break;
      case 3: /* frequency */
      case FREQUENCY:
	soundReg->mode3.frequencyHigh = value >> 8;
	soundReg->mode3.frequencyLow  = value;
	NR33_REG = ((UBYTE *)soundReg)[0x0D];
	NR34_REG = ((UBYTE *)soundReg)[0x0E];
	break;
      case 4: /* counter_ConsSel */
	soundReg->mode3.counter_ConsSel = value;
	NR34_REG = ((UBYTE *)soundReg)[0x0E];
	break;
      case 5: /* Sound3_To_SO1 */
	soundReg->control.Sound3_To_SO1 = value;
	NR51_REG = ((UBYTE *)soundReg)[0x15];
	break;
      case 6: /* Sound3_To_SO2 */
	soundReg->control.Sound3_To_SO2 = value;
	NR51_REG = ((UBYTE *)soundReg)[0x15];
	break;
      case 7: /* Sound3_On_Off */
	soundReg->control.Sound3_On_Off = value;
	NR52_REG = ((UBYTE *)soundReg)[0x16];
	break;
      case PLAY: /* restart */
	update_value(mode, FREQUENCY, current_value(mode, FREQUENCY));
	soundReg->mode3.restart = value;
	NR34_REG = ((UBYTE *)soundReg)[0x0E];
	soundReg->mode3.restart = 0;
	break;
      }
  } else if(mode == 4) {
    switch(line)
      {
      case 0: /* soundLength */
	soundReg->mode4.soundLength = value;
	NR41_REG = ((UBYTE *)soundReg)[0x10];
	break;
      case 1: /* envInitialValue */
	soundReg->mode4.envInitialValue = value;
	NR42_REG = ((UBYTE *)soundReg)[0x11];
	break;
      case 2: /* envMode */
	soundReg->mode4.envMode = value;
	NR42_REG = ((UBYTE *)soundReg)[0x11];
	break;
      case 3: /* envNbStep */
	soundReg->mode4.envNbStep = value;
	NR42_REG = ((UBYTE *)soundReg)[0x11];
	break;
      case 4: /* polyCounterFreq */
	soundReg->mode4.polyCounterFreq = value;
	NR43_REG = ((UBYTE *)soundReg)[0x12];
	break;
      case 5: /* polyCounterStep */
	soundReg->mode4.polyCounterStep = value;
	NR43_REG = ((UBYTE *)soundReg)[0x12];
	break;
      case 6: /* polyCounterDiv */
	soundReg->mode4.polyCounterDiv = value;
	NR43_REG = ((UBYTE *)soundReg)[0x12];
	break;
      case 7: /* counter_ConsSel */
	soundReg->mode4.counter_ConsSel = value;
	NR44_REG = ((UBYTE *)soundReg)[0x13];
	break;
      case 8: /* Sound4_To_SO1 */
	soundReg->control.Sound4_To_SO1 = value;
	NR51_REG = ((UBYTE *)soundReg)[0x15];
	break;
      case 9: /* Sound4_To_SO2 */
	soundReg->control.Sound4_To_SO2 = value;
	NR51_REG = ((UBYTE *)soundReg)[0x15];
	break;
      case 10: /* Sound4_On_Off */
	soundReg->control.Sound4_On_Off = value;
	NR52_REG = ((UBYTE *)soundReg)[0x16];
	break;
      case PLAY: /* restart */
	soundReg->mode4.restart = value;
	NR44_REG = ((UBYTE *)soundReg)[0x13];
	soundReg->mode4.restart = 0;
	break;
      }
  }
}
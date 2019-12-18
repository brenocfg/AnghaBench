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
struct TYPE_11__ {int global_On_Off; int Vin_SO1; int Vin_SO2; int SO1_OutputLevel; int SO2_OutputLevel; int Sound1_To_SO1; int Sound1_To_SO2; int Sound1_On_Off; int Sound2_To_SO1; int Sound2_To_SO2; int Sound2_On_Off; int Sound3_To_SO1; int Sound3_To_SO2; int Sound3_On_Off; int Sound4_To_SO1; int Sound4_To_SO2; int Sound4_On_Off; } ;
struct TYPE_10__ {int soundLength; int envInitialValue; int envMode; int envNbStep; int polyCounterFreq; int polyCounterStep; int polyCounterDiv; int counter_ConsSel; } ;
struct TYPE_9__ {int on_Off; int soundLength; int selOutputLevel; int counter_ConsSel; int /*<<< orphan*/  frequencyLow; int /*<<< orphan*/  frequencyHigh; } ;
struct TYPE_8__ {int patternDuty; int soundLength; int envInitialValue; int envMode; int envNbStep; int counter_ConsSel; int /*<<< orphan*/  frequencyLow; int /*<<< orphan*/  frequencyHigh; } ;
struct TYPE_7__ {int sweepTime; int sweepMode; int sweepShifts; int patternDuty; int soundLength; int envInitialValue; int envMode; int envNbSweep; int counter_ConsSel; int /*<<< orphan*/  frequencyLow; int /*<<< orphan*/  frequencyHigh; } ;
struct TYPE_12__ {TYPE_5__ control; TYPE_4__ mode4; TYPE_3__ mode3; TYPE_2__ mode2; TYPE_1__ mode1; } ;

/* Variables and functions */
#define  FREQUENCY 128 
 TYPE_6__* soundReg ; 

UWORD current_value(UBYTE mode, UBYTE line)
{
  if(mode == 0) {
    switch(line)
      {
      case 0: /* global_On_Off */
	return soundReg->control.global_On_Off;
      case 1: /* Vin_SO1 */
	return soundReg->control.Vin_SO1;
      case 2: /* Vin_SO2 */
	return soundReg->control.Vin_SO2;
      case 3: /* SO1_OutputLevel */
	return soundReg->control.SO1_OutputLevel;
      case 4: /* SO2_OutputLevel */
	return soundReg->control.SO2_OutputLevel;
      }
  } else if(mode == 1) {
    switch(line)
      {
      case 0: /* sweepTime */
	return soundReg->mode1.sweepTime;
      case 1: /* sweepMode */
	return soundReg->mode1.sweepMode;
      case 2: /* sweepShifts */
	return soundReg->mode1.sweepShifts;
      case 3: /* patternDuty */
	return soundReg->mode1.patternDuty;
      case 4: /* soundLength */
	return soundReg->mode1.soundLength;
      case 5: /* envInitialValue */
	return soundReg->mode1.envInitialValue;
      case 6: /* envMode */
	return soundReg->mode1.envMode;
      case 7: /* envNbSweep */
	return soundReg->mode1.envNbSweep;
      case 8: /* frequency */
      case FREQUENCY:
	return ((UWORD)soundReg->mode1.frequencyHigh << 8) +
	  (UWORD)soundReg->mode1.frequencyLow;
      case 9: /* counter_ConsSel */
	return soundReg->mode1.counter_ConsSel;
      case 10: /* Sound1_To_SO1 */
	return soundReg->control.Sound1_To_SO1;
      case 11: /* Sound1_To_SO2 */
	return soundReg->control.Sound1_To_SO2;
      case 12: /* Sound1_On_Off */
	return soundReg->control.Sound1_On_Off;
      }
  } else if(mode == 2) {
    switch(line)
      {
      case 0: /* patternDuty */
	return soundReg->mode2.patternDuty;
      case 1: /* soundLength */
	return soundReg->mode2.soundLength;
      case 2: /* envInitialValue */
	return soundReg->mode2.envInitialValue;
      case 3: /* envMode */
	return soundReg->mode2.envMode;
      case 4: /* envNbStep */
	return soundReg->mode2.envNbStep;
      case 5: /* frequency */
      case FREQUENCY:
	return ((UWORD)soundReg->mode2.frequencyHigh << 8) +
	  (UWORD)soundReg->mode2.frequencyLow;
      case 6: /* counter_ConsSel */
	return soundReg->mode2.counter_ConsSel;
      case 7: /* Sound2_To_SO1 */
	return soundReg->control.Sound2_To_SO1;
      case 8: /* Sound2_To_SO2 */
	return soundReg->control.Sound2_To_SO2;
      case 9: /* Sound2_On_Off */
	return soundReg->control.Sound2_On_Off;
      }
  } else if(mode == 3) {
    switch(line)
      {
      case 0: /* on_Off */
	return soundReg->mode3.on_Off;
      case 1: /* soundLength */
	return soundReg->mode3.soundLength;
      case 2: /* selOutputLevel */
	return soundReg->mode3.selOutputLevel;
      case 3: /* frequency */
      case FREQUENCY:
	return ((UWORD)soundReg->mode3.frequencyHigh << 8) +
	  (UWORD)soundReg->mode3.frequencyLow;
      case 4: /* counter_ConsSel */
	return soundReg->mode3.counter_ConsSel;
      case 5: /* Sound3_To_SO1 */
	return soundReg->control.Sound3_To_SO1;
      case 6: /* Sound3_To_SO2 */
	return soundReg->control.Sound3_To_SO2;
      case 7: /* Sound3_On_Off */
	return soundReg->control.Sound3_On_Off;
      }
  } else if(mode == 4) {
    switch(line)
      {
      case 0: /* soundLength */
	return soundReg->mode4.soundLength;
      case 1: /* envInitialValue */
	return soundReg->mode4.envInitialValue;
      case 2: /* envMode */
	return soundReg->mode4.envMode;
      case 3: /* envNbStep */
	return soundReg->mode4.envNbStep;
      case 4: /* polyCounterFreq */
	return soundReg->mode4.polyCounterFreq;
      case 5: /* polyCounterStep */
	return soundReg->mode4.polyCounterStep;
      case 6: /* polyCounterDiv */
	return soundReg->mode4.polyCounterDiv;
      case 7: /* counter_ConsSel */
	return soundReg->mode4.counter_ConsSel;
      case 8: /* Sound4_To_SO1 */
	return soundReg->control.Sound4_To_SO1;
      case 9: /* Sound4_To_SO2 */
	return soundReg->control.Sound4_To_SO2;
      case 10: /* Sound4_On_Off */
	return soundReg->control.Sound4_On_Off;
      }
  }
  return 0;
}
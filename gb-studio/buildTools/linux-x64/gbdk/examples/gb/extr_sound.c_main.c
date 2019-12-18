#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int member_0; int member_2; int member_4; int member_5; int member_6; int member_7; int member_8; int member_9; int member_10; int member_11; int member_17; int /*<<< orphan*/  member_16; int /*<<< orphan*/  member_15; int /*<<< orphan*/  member_14; int /*<<< orphan*/  member_13; int /*<<< orphan*/  member_12; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_1; } ;
struct TYPE_9__ {int member_1; int member_3; int member_5; int member_10; int /*<<< orphan*/  member_11; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int member_1; int member_4; int member_6; int member_7; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int member_1; int member_2; int member_3; int member_5; int member_6; int member_7; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int member_4; int member_5; int member_6; int member_8; int member_9; int member_10; int /*<<< orphan*/  member_13; int /*<<< orphan*/  member_12; int /*<<< orphan*/  member_11; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct SoundReg {TYPE_5__ member_4; TYPE_4__ member_3; TYPE_3__ member_2; TYPE_2__ member_1; TYPE_1__ member_0; } ;
typedef  void* UBYTE ;

/* Variables and functions */
 void* NR10_REG ; 
 void* NR11_REG ; 
 void* NR12_REG ; 
 void* NR13_REG ; 
 void* NR14_REG ; 
 void* NR21_REG ; 
 void* NR22_REG ; 
 void* NR23_REG ; 
 void* NR24_REG ; 
 void* NR30_REG ; 
 void* NR31_REG ; 
 void* NR32_REG ; 
 void* NR33_REG ; 
 void* NR34_REG ; 
 void* NR41_REG ; 
 void* NR42_REG ; 
 void* NR43_REG ; 
 void* NR44_REG ; 
 void* NR50_REG ; 
 void* NR51_REG ; 
 int NR52_REG ; 
 int /*<<< orphan*/  cls () ; 
 struct SoundReg* soundReg ; 
 int /*<<< orphan*/  wait_event (int) ; 

void main()
{
  struct SoundReg s = {
    { 0, 0, 0, 0,
      1, 2,
      3, 0, 4,
      0x73U,
      6, 0, 0, 0 },
    { 0,
      1, 2,
      4, 0, 8,
      0xD7U,
      6, 0, 0, 0 },
    { 0, 1,
      0,
      0, 1, 0,
      0xD6U,
      6, 0, 0, 0 },
    { 0,
      58, 0,
      1, 0, 10,
      0, 0, 0,
      0, 1, 0 },
    { 7, 0, 7, 0,
      1, 1, 1, 1, 1, 1, 1, 1,
      0, 0, 0, 0, 0, 1 }
  };

  /*
   * Before modifying any sound register, sound must be turned on!
   * (it is turned off by default to save batteries)
   */
  NR52_REG = 0x80;

  soundReg = &s;
  NR10_REG = ((UBYTE *)soundReg)[0x00];
  NR11_REG = ((UBYTE *)soundReg)[0x01];
  NR12_REG = ((UBYTE *)soundReg)[0x02];
  NR13_REG = ((UBYTE *)soundReg)[0x03];
  NR14_REG = ((UBYTE *)soundReg)[0x04];

  NR21_REG = ((UBYTE *)soundReg)[0x06];
  NR22_REG = ((UBYTE *)soundReg)[0x07];
  NR23_REG = ((UBYTE *)soundReg)[0x08];
  NR24_REG = ((UBYTE *)soundReg)[0x09];

  NR30_REG = ((UBYTE *)soundReg)[0x0A];
  NR31_REG = ((UBYTE *)soundReg)[0x0B];
  NR32_REG = ((UBYTE *)soundReg)[0x0C];
  NR33_REG = ((UBYTE *)soundReg)[0x0D];
  NR34_REG = ((UBYTE *)soundReg)[0x0E];

  NR41_REG = ((UBYTE *)soundReg)[0x10];
  NR42_REG = ((UBYTE *)soundReg)[0x11];
  NR43_REG = ((UBYTE *)soundReg)[0x12];
  NR44_REG = ((UBYTE *)soundReg)[0x13];

  NR50_REG = ((UBYTE *)soundReg)[0x14];
  NR51_REG = ((UBYTE *)soundReg)[0x15];
  NR52_REG = ((UBYTE *)soundReg)[0x16];

  cls();

  wait_event(1);
}
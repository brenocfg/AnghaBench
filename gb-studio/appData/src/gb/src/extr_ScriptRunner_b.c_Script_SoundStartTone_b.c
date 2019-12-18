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
typedef  int UWORD ;

/* Variables and functions */
 int NR10_REG ; 
 int NR11_REG ; 
 int NR12_REG ; 
 int NR13_REG ; 
 int NR14_REG ; 
 int NR50_REG ; 
 int NR51_REG ; 
 int NR52_REG ; 
 int /*<<< orphan*/  TRUE ; 
 int* script_cmd_args ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_continue ; 
 int /*<<< orphan*/  script_ptr ; 

void Script_SoundStartTone_b()
{
  UWORD tone = (script_cmd_args[0] * 256) + script_cmd_args[1];

  // enable sound
  NR52_REG = 0x80;

  // play tone on channel 1
  NR10_REG = 0x00;
  NR11_REG = (0x00 << 6) | 0x01;
  NR12_REG = (0x0F << 4) | 0x00;
  NR13_REG = (tone & 0x00FF);
  NR14_REG = 0x80 | ((tone & 0x0700) >> 8);

  // enable volume
  NR50_REG = 0x77;

  // enable channel 1
  NR51_REG |= 0x11;

  script_ptr += 1 + script_cmd_args_len;
  script_continue = TRUE;
}
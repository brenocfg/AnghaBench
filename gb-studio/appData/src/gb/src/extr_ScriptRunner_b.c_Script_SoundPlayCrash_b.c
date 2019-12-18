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
 int NR41_REG ; 
 int NR42_REG ; 
 int NR43_REG ; 
 int NR44_REG ; 
 int NR50_REG ; 
 int NR51_REG ; 
 int NR52_REG ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_continue ; 
 int /*<<< orphan*/  script_ptr ; 

void Script_SoundPlayCrash_b()
{
  // enable sound
  NR52_REG = 0x80;

  // play crash sound on channel 4
  NR41_REG = 0x01;
  NR42_REG = (0x0F << 4) | 0x02;
  NR43_REG = 0x13;
  NR44_REG = 0x80;

  // enable volume
  NR50_REG = 0x77;

  // enable channel 4
  NR51_REG |= 0x88;

  // no delay
  script_ptr += 1 + script_cmd_args_len;
  script_continue = TRUE;
}
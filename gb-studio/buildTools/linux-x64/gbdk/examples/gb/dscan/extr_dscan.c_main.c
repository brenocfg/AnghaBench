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
 int /*<<< orphan*/  DISPLAY_OFF ; 
 int /*<<< orphan*/  DISPLAY_ON ; 
 int /*<<< orphan*/  J_A ; 
 int /*<<< orphan*/  J_B ; 
 int /*<<< orphan*/  bombs () ; 
 int /*<<< orphan*/  delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_interrupts () ; 
 int /*<<< orphan*/  enable_interrupts () ; 
 int /*<<< orphan*/  enemys () ; 
 int /*<<< orphan*/  init_enemy () ; 
 int /*<<< orphan*/  init_kirai () ; 
 int /*<<< orphan*/  init_player () ; 
 int /*<<< orphan*/  init_score () ; 
 int /*<<< orphan*/  init_screen () ; 
 int /*<<< orphan*/  init_tama () ; 
 int /*<<< orphan*/  k_left ; 
 int /*<<< orphan*/  k_right ; 
 int /*<<< orphan*/  kirai () ; 
 int /*<<< orphan*/  player () ; 
 int /*<<< orphan*/  pw ; 
 int /*<<< orphan*/  show_gover () ; 

void main()
{
  disable_interrupts();
  DISPLAY_OFF;

  init_screen();
  init_score();
  init_player();
  init_tama();
  init_enemy();
  init_kirai();
  show_gover();
  k_right = J_A;
  k_left = J_B;
  DISPLAY_ON;
  enable_interrupts();

  while(1) {
    delay( pw );
    player();
    bombs();
    enemys();
    kirai();
  }
}
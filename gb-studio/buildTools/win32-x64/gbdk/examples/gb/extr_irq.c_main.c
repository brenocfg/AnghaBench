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
 int TAC_REG ; 
 int TIM_IFLAG ; 
 int TMA_REG ; 
 int VBL_IFLAG ; 
 int /*<<< orphan*/  add_TIM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_VBL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delay (unsigned long) ; 
 int /*<<< orphan*/  disable_interrupts () ; 
 int /*<<< orphan*/  enable_interrupts () ; 
 int /*<<< orphan*/  print_counter () ; 
 int /*<<< orphan*/  set_interrupts (int) ; 
 int /*<<< orphan*/  tim ; 
 scalar_t__ tim_cnt ; 
 int /*<<< orphan*/  vbl ; 
 scalar_t__ vbl_cnt ; 

void main()
{
  /* Ensure mutual exclusion (not really necessary in this example)... */
  disable_interrupts();
  vbl_cnt = tim_cnt = 0;
  add_VBL(vbl);
  add_TIM(tim);
  enable_interrupts();

  /* Set TMA to divide clock by 0x100 */
  TMA_REG = 0x00U;
  /* Set clock to 4096 Hertz */
  TAC_REG = 0x04U;
  /* Handle VBL and TIM interrupts */
  set_interrupts(VBL_IFLAG | TIM_IFLAG);

  while(1) {
    print_counter();
    delay(1000UL);
  }
}
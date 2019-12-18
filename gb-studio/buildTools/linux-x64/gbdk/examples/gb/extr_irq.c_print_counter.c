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
typedef  scalar_t__ UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  disable_interrupts () ; 
 int /*<<< orphan*/  enable_interrupts () ; 
 int /*<<< orphan*/  gotoxy (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posy () ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 
 scalar_t__ tim_cnt ; 
 scalar_t__ vbl_cnt ; 

void print_counter()
{
  UBYTE cnt;

  /* Ensure mutual exclusion (not really necessary in this example)... */
  disable_interrupts();
  cnt = tim_cnt;
  enable_interrupts();

  printf(" TIM %u", (unsigned int)cnt);
  gotoxy(9, posy());

  /* Ensure mutual exclusion (not really necessary in this example)... */
  disable_interrupts();
  cnt = vbl_cnt;
  enable_interrupts();

  printf("- VBL %u\n", (unsigned int)cnt);
}
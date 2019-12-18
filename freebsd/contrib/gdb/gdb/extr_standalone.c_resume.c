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
typedef  int /*<<< orphan*/  REGISTER_TYPE ;

/* Variables and functions */
 int NUM_REGS ; 
 int /*<<< orphan*/  POP_REGISTERS ; 
 int /*<<< orphan*/  PUSH_FRAME_PTR ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  save_frame_pointer () ; 
 int /*<<< orphan*/  saved_regs ; 

resume (void)
{
  REGISTER_TYPE restore[NUM_REGS];

  PUSH_FRAME_PTR;
  save_frame_pointer ();

  memcpy (restore, saved_regs, sizeof restore);
  POP_REGISTERS;
  /* Control does not drop through here!  */
}
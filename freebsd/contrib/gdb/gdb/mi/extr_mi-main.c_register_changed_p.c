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
 size_t DEPRECATED_REGISTER_BYTE (int) ; 
 int /*<<< orphan*/  DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 int MAX_REGISTER_SIZE ; 
 int /*<<< orphan*/  deprecated_selected_frame ; 
 int /*<<< orphan*/  frame_register_read (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * old_regs ; 

__attribute__((used)) static int
register_changed_p (int regnum)
{
  char raw_buffer[MAX_REGISTER_SIZE];

  if (! frame_register_read (deprecated_selected_frame, regnum, raw_buffer))
    return -1;

  if (memcmp (&old_regs[DEPRECATED_REGISTER_BYTE (regnum)], raw_buffer,
	      DEPRECATED_REGISTER_RAW_SIZE (regnum)) == 0)
    return 0;

  /* Found a changed register. Return 1. */

  memcpy (&old_regs[DEPRECATED_REGISTER_BYTE (regnum)], raw_buffer,
	  DEPRECATED_REGISTER_RAW_SIZE (regnum));

  return 1;
}
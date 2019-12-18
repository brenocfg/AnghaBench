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
struct value {int dummy; } ;
struct frame_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ SP_REGNUM ; 
 int /*<<< orphan*/  error (char*) ; 
 struct value* value_of_register (scalar_t__,struct frame_info*) ; 

__attribute__((used)) static struct value *
value_of_builtin_frame_sp_reg (struct frame_info *frame)
{
#ifdef SP_REGNUM
  if (SP_REGNUM >= 0)
    return value_of_register (SP_REGNUM, frame);
#endif
  error ("Standard register ``$sp'' is not available for this target");
}
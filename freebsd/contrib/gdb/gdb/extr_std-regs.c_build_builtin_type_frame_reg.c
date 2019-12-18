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
 int /*<<< orphan*/  TYPE_CODE_STRUCT ; 
 int /*<<< orphan*/  append_composite_type_field (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * builtin_type_frame_reg ; 
 int /*<<< orphan*/  builtin_type_void_data_ptr ; 
 int /*<<< orphan*/ * init_composite_type (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
build_builtin_type_frame_reg (void)
{
  /* $frame.  */
  if (builtin_type_frame_reg == NULL)
    {
#if 0
      struct frame
      {
	void *base;
      };
#endif
      builtin_type_frame_reg = init_composite_type ("frame", TYPE_CODE_STRUCT);
      append_composite_type_field (builtin_type_frame_reg, "base",
				   builtin_type_void_data_ptr);
    }
}
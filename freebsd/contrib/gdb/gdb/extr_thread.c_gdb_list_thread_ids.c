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
struct ui_out {int dummy; } ;
typedef  enum gdb_rc { ____Placeholder_gdb_rc } gdb_rc ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 int catch_exceptions (struct ui_out*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_captured_list_thread_ids ; 

enum gdb_rc
gdb_list_thread_ids (struct ui_out *uiout)
{
  return catch_exceptions (uiout, do_captured_list_thread_ids, NULL,
			   NULL, RETURN_MASK_ALL);
}
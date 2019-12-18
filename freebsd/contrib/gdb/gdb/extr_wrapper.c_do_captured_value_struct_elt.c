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
struct captured_value_struct_elt_args {int /*<<< orphan*/  err; int /*<<< orphan*/  static_memfuncp; int /*<<< orphan*/  name; int /*<<< orphan*/  args; int /*<<< orphan*/  argp; int /*<<< orphan*/ * result_ptr; } ;

/* Variables and functions */
 int GDB_RC_OK ; 
 int /*<<< orphan*/  value_struct_elt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
do_captured_value_struct_elt (struct ui_out *uiout, void *data)
{
  struct captured_value_struct_elt_args *cargs = data;
  *cargs->result_ptr = value_struct_elt (cargs->argp, cargs->args, cargs->name,
			     cargs->static_memfuncp, cargs->err);
  return GDB_RC_OK;
}
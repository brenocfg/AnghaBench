#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct target_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* to_files_info ) (struct target_ops*) ;} ;

/* Variables and functions */
 TYPE_1__ debug_target ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  stub1 (struct target_ops*) ; 

__attribute__((used)) static void
debug_to_files_info (struct target_ops *target)
{
  debug_target.to_files_info (target);

  fprintf_unfiltered (gdb_stdlog, "target_files_info (xxx)\n");
}
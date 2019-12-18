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
 TYPE_1__ procfs_ops ; 
 int /*<<< orphan*/  stub1 (struct target_ops*) ; 

__attribute__((used)) static void
sol_thread_files_info (struct target_ops *ignore)
{
  procfs_ops.to_files_info (ignore);
}
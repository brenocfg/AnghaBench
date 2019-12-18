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
struct mem_ctl_info {int dummy; } ;
struct i5000_error_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i5000_process_fatal_error_info (struct mem_ctl_info*,struct i5000_error_info*,int) ; 
 int /*<<< orphan*/  i5000_process_nonfatal_error_info (struct mem_ctl_info*,struct i5000_error_info*,int) ; 

__attribute__((used)) static void i5000_process_error_info(struct mem_ctl_info *mci,
				struct i5000_error_info *info,
				int handle_errors)
{
	/* First handle any fatal errors that occurred */
	i5000_process_fatal_error_info(mci, info, handle_errors);

	/* now handle any non-fatal errors that occurred */
	i5000_process_nonfatal_error_info(mci, info, handle_errors);
}
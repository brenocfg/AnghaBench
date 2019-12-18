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
struct e7xxx_error_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  e7xxx_get_error_info (struct mem_ctl_info*,struct e7xxx_error_info*) ; 
 int /*<<< orphan*/  e7xxx_process_error_info (struct mem_ctl_info*,struct e7xxx_error_info*,int) ; 
 int /*<<< orphan*/  edac_dbg (int,char*) ; 

__attribute__((used)) static void e7xxx_check(struct mem_ctl_info *mci)
{
	struct e7xxx_error_info info;

	edac_dbg(3, "\n");
	e7xxx_get_error_info(mci, &info);
	e7xxx_process_error_info(mci, &info, 1);
}
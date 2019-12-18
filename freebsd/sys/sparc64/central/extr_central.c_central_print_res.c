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
struct central_devinfo {int /*<<< orphan*/  cdi_rl; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int resource_list_print_type (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
central_print_res(struct central_devinfo *cdi)
{

	return (resource_list_print_type(&cdi->cdi_rl, "mem", SYS_RES_MEMORY,
	    "%#jx"));
}
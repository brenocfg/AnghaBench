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
struct sbus_devinfo {int /*<<< orphan*/  sdi_rl; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ resource_list_print_type (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
sbus_print_res(struct sbus_devinfo *sdi)
{
	int rv;

	rv = 0;
	rv += resource_list_print_type(&sdi->sdi_rl, "mem", SYS_RES_MEMORY,
	    "%#jx");
	rv += resource_list_print_type(&sdi->sdi_rl, "irq", SYS_RES_IRQ,
	    "%jd");
	return (rv);
}
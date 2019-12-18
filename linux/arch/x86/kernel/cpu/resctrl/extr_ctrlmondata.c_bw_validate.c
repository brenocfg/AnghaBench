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
struct TYPE_2__ {unsigned long min_bw; scalar_t__ bw_gran; int /*<<< orphan*/  delay_linear; } ;
struct rdt_resource {unsigned long default_ctrl; TYPE_1__ membw; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_mba_sc (struct rdt_resource*) ; 
 int kstrtoul (char*,int,unsigned long*) ; 
 int /*<<< orphan*/  rdt_last_cmd_printf (char*,...) ; 
 int /*<<< orphan*/  rdt_last_cmd_puts (char*) ; 
 unsigned long roundup (unsigned long,unsigned long) ; 

__attribute__((used)) static bool bw_validate(char *buf, unsigned long *data, struct rdt_resource *r)
{
	unsigned long bw;
	int ret;

	/*
	 * Only linear delay values is supported for current Intel SKUs.
	 */
	if (!r->membw.delay_linear) {
		rdt_last_cmd_puts("No support for non-linear MB domains\n");
		return false;
	}

	ret = kstrtoul(buf, 10, &bw);
	if (ret) {
		rdt_last_cmd_printf("Non-decimal digit in MB value %s\n", buf);
		return false;
	}

	if ((bw < r->membw.min_bw || bw > r->default_ctrl) &&
	    !is_mba_sc(r)) {
		rdt_last_cmd_printf("MB value %ld out of range [%d,%d]\n", bw,
				    r->membw.min_bw, r->default_ctrl);
		return false;
	}

	*data = roundup(bw, (unsigned long)r->membw.bw_gran);
	return true;
}
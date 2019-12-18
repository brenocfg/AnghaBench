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
struct rdt_resource {int dummy; } ;
struct rdt_parse_data {int /*<<< orphan*/  buf; } ;
struct rdt_domain {int have_new_ctrl; unsigned long new_ctrl; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bw_validate_amd (int /*<<< orphan*/ ,unsigned long*,struct rdt_resource*) ; 
 int /*<<< orphan*/  rdt_last_cmd_printf (char*,int /*<<< orphan*/ ) ; 

int parse_bw_amd(struct rdt_parse_data *data, struct rdt_resource *r,
		 struct rdt_domain *d)
{
	unsigned long bw_val;

	if (d->have_new_ctrl) {
		rdt_last_cmd_printf("Duplicate domain %d\n", d->id);
		return -EINVAL;
	}

	if (!bw_validate_amd(data->buf, &bw_val, r))
		return -EINVAL;

	d->new_ctrl = bw_val;
	d->have_new_ctrl = true;

	return 0;
}
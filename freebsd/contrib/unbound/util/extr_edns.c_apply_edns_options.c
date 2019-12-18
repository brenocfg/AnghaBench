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
struct regional {int dummy; } ;
struct edns_data {int dummy; } ;
struct config_file {scalar_t__ do_tcp_keepalive; } ;
struct comm_point {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  edns_keepalive (struct edns_data*,struct edns_data*,struct comm_point*,struct regional*) ; 

int apply_edns_options(struct edns_data* edns_out, struct edns_data* edns_in,
	struct config_file* cfg, struct comm_point* c, struct regional* region)
{
	if(cfg->do_tcp_keepalive &&
		!edns_keepalive(edns_out, edns_in, c, region))
		return 0;

	return 1;
}
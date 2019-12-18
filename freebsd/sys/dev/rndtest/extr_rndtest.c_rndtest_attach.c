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
struct rndtest_state {int rs_discard; int rs_collect; int /*<<< orphan*/  rs_to; int /*<<< orphan*/  rs_parent; scalar_t__ rs_begin; scalar_t__ rs_current; scalar_t__ rs_buf; scalar_t__ rs_end; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct rndtest_state* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct rndtest_state *
rndtest_attach(device_t dev)
{
	struct rndtest_state *rsp;

	rsp = malloc(sizeof (*rsp), M_DEVBUF, M_NOWAIT);
	if (rsp != NULL) {
		rsp->rs_begin = rsp->rs_buf;
		rsp->rs_end = rsp->rs_buf + sizeof(rsp->rs_buf);
		rsp->rs_current = rsp->rs_begin;
		rsp->rs_discard = 1;
		rsp->rs_collect = 1;
		rsp->rs_parent = dev;
#if __FreeBSD_version < 500000
		callout_init(&rsp->rs_to);
#else
		callout_init(&rsp->rs_to, 1);
#endif
	} else
		device_printf(dev, "rndtest_init: no memory for state block\n");
	return (rsp);
}
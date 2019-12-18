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
struct wbt_wait_data {int wb_acct; unsigned long rw; struct rq_wb* rwb; } ;
struct rq_wb {int dummy; } ;
struct rq_wait {int dummy; } ;
typedef  enum wbt_flags { ____Placeholder_wbt_flags } wbt_flags ;

/* Variables and functions */
 struct rq_wait* get_rq_wait (struct rq_wb*,int) ; 
 int /*<<< orphan*/  rq_qos_wait (struct rq_wait*,struct wbt_wait_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wbt_cleanup_cb ; 
 int /*<<< orphan*/  wbt_inflight_cb ; 

__attribute__((used)) static void __wbt_wait(struct rq_wb *rwb, enum wbt_flags wb_acct,
		       unsigned long rw)
{
	struct rq_wait *rqw = get_rq_wait(rwb, wb_acct);
	struct wbt_wait_data data = {
		.rwb = rwb,
		.wb_acct = wb_acct,
		.rw = rw,
	};

	rq_qos_wait(rqw, &data, wbt_inflight_cb, wbt_cleanup_cb);
}
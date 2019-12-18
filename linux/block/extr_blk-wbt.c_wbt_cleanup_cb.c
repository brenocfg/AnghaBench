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
struct wbt_wait_data {int /*<<< orphan*/  wb_acct; int /*<<< orphan*/  rwb; } ;
struct rq_wait {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wbt_rqw_done (int /*<<< orphan*/ ,struct rq_wait*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wbt_cleanup_cb(struct rq_wait *rqw, void *private_data)
{
	struct wbt_wait_data *data = private_data;
	wbt_rqw_done(data->rwb, rqw, data->wb_acct);
}
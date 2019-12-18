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
struct wbt_wait_data {int /*<<< orphan*/  rw; int /*<<< orphan*/  rwb; } ;
struct rq_wait {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rq_wait_inc_below (struct rq_wait*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool wbt_inflight_cb(struct rq_wait *rqw, void *private_data)
{
	struct wbt_wait_data *data = private_data;
	return rq_wait_inc_below(rqw, get_limit(data->rwb, data->rw));
}
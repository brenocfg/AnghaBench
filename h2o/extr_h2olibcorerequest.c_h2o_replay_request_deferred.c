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
struct st_deferred_request_action_t {int dummy; } ;
typedef  int /*<<< orphan*/  h2o_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  create_deferred_action (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_replay_request_cb ; 

void h2o_replay_request_deferred(h2o_req_t *req)
{
    create_deferred_action(req, sizeof(struct st_deferred_request_action_t), on_replay_request_cb);
}
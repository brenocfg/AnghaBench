#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rp_generator_t {int /*<<< orphan*/  send_headers_timeout; int /*<<< orphan*/ * client; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* cancel ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ h2o_httpclient_t ;

/* Variables and functions */
 TYPE_1__* detach_client (struct rp_generator_t*) ; 
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void do_close(struct rp_generator_t *self)
{
    /**
     * This can be called in the following three scenarios:
     *   1. Downstream timeout before receiving header from upstream
     *        dispose callback calls this function, but stop callback doesn't
     *   2. Reprocess
     *        stop callback calls this, but dispose callback does it later (after reprocessed request gets finished)
     *   3. Others
     *        Both of stop and dispose callbacks call this function in order
     * Thus, to ensure to do closing things, both of dispose and stop callbacks call this function.
     */
    if (self->client != NULL) {
        h2o_httpclient_t *client = detach_client(self);
        client->cancel(client);
    }
    h2o_timer_unlink(&self->send_headers_timeout);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  inflight; } ;
struct TYPE_6__ {TYPE_1__ sending; } ;
struct st_fcgi_generator_t {TYPE_2__ resp; int /*<<< orphan*/  timeout; int /*<<< orphan*/ * sock; TYPE_4__* handler; } ;
struct TYPE_7__ {scalar_t__ keepalive_timeout; } ;
struct TYPE_8__ {int /*<<< orphan*/  sockpool; TYPE_3__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_send (struct st_fcgi_generator_t*) ; 
 int /*<<< orphan*/  h2o_socket_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_socketpool_return (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ h2o_timer_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void send_eos_and_close(struct st_fcgi_generator_t *generator, int can_keepalive)
{
    if (generator->handler->config.keepalive_timeout != 0 && can_keepalive)
        h2o_socketpool_return(&generator->handler->sockpool, generator->sock);
    else
        h2o_socket_close(generator->sock);
    generator->sock = NULL;
    if (h2o_timer_is_linked(&generator->timeout))
        h2o_timer_unlink(&generator->timeout);
    if (!generator->resp.sending.inflight)
        do_send(generator);
}
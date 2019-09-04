#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * buf; } ;
struct TYPE_3__ {int /*<<< orphan*/ * receiving; TYPE_2__ sending; } ;
struct st_fcgi_generator_t {TYPE_1__ resp; int /*<<< orphan*/ * sock; int /*<<< orphan*/ * connect_req; int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_buffer_dispose (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  h2o_doublebuffer_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  h2o_socket_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_socketpool_cancel_connect (int /*<<< orphan*/ *) ; 
 scalar_t__ h2o_timer_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_generator(struct st_fcgi_generator_t *generator)
{
    /* can be called more than once */
    if (h2o_timer_is_linked(&generator->timeout))
        h2o_timer_unlink(&generator->timeout);
    if (generator->connect_req != NULL) {
        h2o_socketpool_cancel_connect(generator->connect_req);
        generator->connect_req = NULL;
    }
    if (generator->sock != NULL) {
        h2o_socket_close(generator->sock);
        generator->sock = NULL;
    }
    if (generator->resp.sending.buf != NULL)
        h2o_doublebuffer_dispose(&generator->resp.sending);
    if (generator->resp.receiving != NULL)
        h2o_buffer_dispose(&generator->resp.receiving);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct st_fcgi_generator_t {TYPE_2__* handler; } ;
struct TYPE_7__ {struct st_fcgi_generator_t* data; } ;
typedef  TYPE_3__ h2o_socket_t ;
struct TYPE_5__ {int /*<<< orphan*/  io_timeout; } ;
struct TYPE_6__ {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  on_rw_timeout ; 
 int /*<<< orphan*/  set_timeout (struct st_fcgi_generator_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_send_complete(h2o_socket_t *sock, const char *err)
{
    struct st_fcgi_generator_t *generator = sock->data;

    set_timeout(generator, generator->handler->config.io_timeout, on_rw_timeout);
    /* do nothing else!  all the rest is handled by the on_read */
}
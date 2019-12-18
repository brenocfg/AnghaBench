#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; TYPE_3__* input; } ;
typedef  TYPE_1__ h2o_socket_t ;
struct TYPE_5__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_buffer_consume (TYPE_3__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_fatal (char*,char const*) ; 
 int /*<<< orphan*/  queue_cb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_read(h2o_socket_t *sock, const char *err)
{
    if (err != NULL) {
        h2o_fatal("on_read: %s", err);
    }

    h2o_buffer_consume(&sock->input, sock->input->size);
    queue_cb(sock->data);
}
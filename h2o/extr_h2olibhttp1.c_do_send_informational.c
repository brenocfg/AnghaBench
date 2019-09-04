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
struct TYPE_3__ {scalar_t__ size; int /*<<< orphan*/  entries; } ;
struct TYPE_4__ {int sending; TYPE_1__ bufs; } ;
struct st_h2o_http1_finalostream_t {TYPE_2__ informational; } ;
typedef  int /*<<< orphan*/  h2o_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_socket_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_send_informational ; 

__attribute__((used)) static void do_send_informational(struct st_h2o_http1_finalostream_t *self, h2o_socket_t *sock)
{
    if (self->informational.sending || self->informational.bufs.size == 0)
        return;

    self->informational.sending = 1;
    h2o_socket_write(sock, self->informational.bufs.entries, self->informational.bufs.size, on_send_informational);
    self->informational.bufs.size = 0;
}
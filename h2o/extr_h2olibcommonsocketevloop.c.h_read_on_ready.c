#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  (* read ) (TYPE_5__*,char const*) ;} ;
struct TYPE_12__ {size_t bytes_read; TYPE_4__ _cb; TYPE_6__* input; TYPE_3__* ssl; } ;
struct st_h2o_evloop_socket_t {int _flags; TYPE_5__ super; int /*<<< orphan*/  fd; } ;
struct TYPE_13__ {size_t size; } ;
struct TYPE_9__ {int /*<<< orphan*/ * cb; } ;
struct TYPE_8__ {TYPE_6__* encrypted; } ;
struct TYPE_10__ {TYPE_2__ handshake; TYPE_1__ input; } ;

/* Variables and functions */
 int H2O_SOCKET_FLAG_DONT_READ ; 
 char* decode_ssl_input (TYPE_5__*) ; 
 char* on_read_core (int /*<<< orphan*/ ,TYPE_6__**) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,char const*) ; 

__attribute__((used)) static void read_on_ready(struct st_h2o_evloop_socket_t *sock)
{
    const char *err = 0;
    size_t prev_bytes_read = sock->super.input->size;

    if ((sock->_flags & H2O_SOCKET_FLAG_DONT_READ) != 0)
        goto Notify;

    if ((err = on_read_core(sock->fd, sock->super.ssl == NULL ? &sock->super.input : &sock->super.ssl->input.encrypted)) != NULL)
        goto Notify;

    if (sock->super.ssl != NULL && sock->super.ssl->handshake.cb == NULL)
        err = decode_ssl_input(&sock->super);

Notify:
    /* the application may get notified even if no new data is avaiable.  The
     * behavior is intentional; it is designed as such so that the applications
     * can update their timeout counters when a partial SSL record arrives.
     */
    sock->super.bytes_read = sock->super.input->size - prev_bytes_read;
    sock->super._cb.read(&sock->super, err);
}
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
struct TYPE_3__ {int /*<<< orphan*/  smallbufs; int /*<<< orphan*/  bufs; } ;
struct TYPE_4__ {int /*<<< orphan*/  input; } ;
struct st_h2o_evloop_socket_t {int fd; int _flags; struct st_h2o_evloop_socket_t* _next_statechanged; struct st_h2o_evloop_socket_t* _next_pending; TYPE_1__ _wreq; int /*<<< orphan*/ * loop; TYPE_2__ super; } ;
typedef  int /*<<< orphan*/  h2o_evloop_t ;

/* Variables and functions */
 int /*<<< orphan*/  evloop_do_on_socket_create (struct st_h2o_evloop_socket_t*) ; 
 int /*<<< orphan*/  h2o_buffer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct st_h2o_evloop_socket_t* h2o_mem_alloc (int) ; 
 int /*<<< orphan*/  h2o_socket_buffer_prototype ; 
 int /*<<< orphan*/  memset (struct st_h2o_evloop_socket_t*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct st_h2o_evloop_socket_t *create_socket(h2o_evloop_t *loop, int fd, int flags)
{
    struct st_h2o_evloop_socket_t *sock;

    sock = h2o_mem_alloc(sizeof(*sock));
    memset(sock, 0, sizeof(*sock));
    h2o_buffer_init(&sock->super.input, &h2o_socket_buffer_prototype);
    sock->loop = loop;
    sock->fd = fd;
    sock->_flags = flags;
    sock->_wreq.bufs = sock->_wreq.smallbufs;
    sock->_next_pending = sock;
    sock->_next_statechanged = sock;

    evloop_do_on_socket_create(sock);

    return sock;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct st_h2o_tunnel_t {TYPE_1__** sock; } ;
struct TYPE_5__ {TYPE_4__* input; struct st_h2o_tunnel_t* data; } ;
typedef  TYPE_1__ h2o_socket_t ;
struct TYPE_6__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close_connection (struct st_h2o_tunnel_t*) ; 
 int /*<<< orphan*/  h2o_buffer_consume (TYPE_4__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_read_start (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_read ; 
 int /*<<< orphan*/  reset_timeout (struct st_h2o_tunnel_t*) ; 

__attribute__((used)) static void on_write_complete(h2o_socket_t *sock, const char *err)
{
    struct st_h2o_tunnel_t *tunnel = sock->data;
    h2o_socket_t *peer;
    assert(tunnel != NULL);
    assert(tunnel->sock[0] == sock || tunnel->sock[1] == sock);

    if (err != NULL) {
        close_connection(tunnel);
        return;
    }

    reset_timeout(tunnel);

    if (tunnel->sock[0] == sock)
        peer = tunnel->sock[1];
    else
        peer = tunnel->sock[0];

    h2o_buffer_consume(&peer->input, peer->input->size);
    h2o_socket_read_start(peer, on_read);
}
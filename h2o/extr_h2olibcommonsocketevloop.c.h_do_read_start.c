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
struct st_h2o_evloop_socket_t {int dummy; } ;
typedef  int /*<<< orphan*/  h2o_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  link_to_statechanged (struct st_h2o_evloop_socket_t*) ; 

void do_read_start(h2o_socket_t *_sock)
{
    struct st_h2o_evloop_socket_t *sock = (struct st_h2o_evloop_socket_t *)_sock;

    link_to_statechanged(sock);
}
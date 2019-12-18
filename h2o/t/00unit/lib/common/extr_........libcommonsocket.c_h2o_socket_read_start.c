#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  read; } ;
struct TYPE_6__ {TYPE_1__ _cb; } ;
typedef  TYPE_2__ h2o_socket_t ;
typedef  int /*<<< orphan*/  h2o_socket_cb ;

/* Variables and functions */
 int /*<<< orphan*/  do_read_start (TYPE_2__*) ; 

void h2o_socket_read_start(h2o_socket_t *sock, h2o_socket_cb cb)
{
    sock->_cb.read = cb;
    do_read_start(sock);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_socket_t ;
typedef  int /*<<< orphan*/  h2o_evloop_t ;
struct TYPE_2__ {int /*<<< orphan*/  super; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 TYPE_1__* create_socket_set_nodelay (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

h2o_socket_t *h2o_evloop_socket_create(h2o_evloop_t *loop, int fd, int flags)
{
    /* it is the reponsibility of the event loop to modify the properties of a socket for its use (i.e., set O_NONBLOCK) */
    fcntl(fd, F_SETFL, O_NONBLOCK);
    return &create_socket_set_nodelay(loop, fd, flags)->super;
}
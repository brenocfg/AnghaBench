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
struct sockaddr {int dummy; } ;
struct listener_config_t {scalar_t__ addrlen; int /*<<< orphan*/  addr; } ;
typedef  scalar_t__ socklen_t ;
struct TYPE_2__ {size_t num_listeners; struct listener_config_t** listeners; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 scalar_t__ h2o_socket_compare_address (void*,struct sockaddr*) ; 

__attribute__((used)) static struct listener_config_t *find_listener(struct sockaddr *addr, socklen_t addrlen)
{
    size_t i;

    for (i = 0; i != conf.num_listeners; ++i) {
        struct listener_config_t *listener = conf.listeners[i];
        if (listener->addrlen == addrlen && h2o_socket_compare_address((void *)&listener->addr, addr) == 0)
            return listener;
    }

    return NULL;
}
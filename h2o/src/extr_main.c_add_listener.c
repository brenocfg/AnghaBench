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
struct listener_config_t {int fd; int proxy_protocol; int /*<<< orphan*/  quic; int /*<<< orphan*/  ssl; int /*<<< orphan*/ ** hosts; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_2__ {int num_listeners; struct listener_config_t** listeners; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 void* h2o_mem_alloc (int) ; 
 struct listener_config_t** h2o_mem_realloc (struct listener_config_t**,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct listener_config_t *add_listener(int fd, struct sockaddr *addr, socklen_t addrlen, int is_global, int proxy_protocol)
{
    struct listener_config_t *listener = h2o_mem_alloc(sizeof(*listener));

    memcpy(&listener->addr, addr, addrlen);
    listener->fd = fd;
    listener->addrlen = addrlen;
    if (is_global) {
        listener->hosts = NULL;
    } else {
        listener->hosts = h2o_mem_alloc(sizeof(listener->hosts[0]));
        listener->hosts[0] = NULL;
    }
    memset(&listener->ssl, 0, sizeof(listener->ssl));
    listener->proxy_protocol = proxy_protocol;
    memset(&listener->quic, 0, sizeof(listener->quic));

    conf.listeners = h2o_mem_realloc(conf.listeners, sizeof(*conf.listeners) * (conf.num_listeners + 1));
    conf.listeners[conf.num_listeners++] = listener;

    return listener;
}
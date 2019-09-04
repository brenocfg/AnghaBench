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
typedef  int /*<<< orphan*/  uv_tcp_t ;
typedef  int /*<<< orphan*/  uv_getaddrinfo_t ;
typedef  int /*<<< orphan*/  uv_connect_t ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct addrinfo {scalar_t__ ai_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  loop ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  on_connect ; 
 int /*<<< orphan*/  stderr ; 
 char* uv_err_name (int) ; 
 int /*<<< orphan*/  uv_freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  uv_ip4_name (struct sockaddr_in*,char*,int) ; 
 int /*<<< orphan*/  uv_tcp_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void on_resolved(uv_getaddrinfo_t *resolver, int status, struct addrinfo *res) {
    if (status < 0) {
        fprintf(stderr, "getaddrinfo callback error %s\n", uv_err_name(status));
        return;
    }

    char addr[17] = {'\0'};
    uv_ip4_name((struct sockaddr_in*) res->ai_addr, addr, 16);
    fprintf(stderr, "%s\n", addr);

    uv_connect_t *connect_req = (uv_connect_t*) malloc(sizeof(uv_connect_t));
    uv_tcp_t *socket = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, socket);

    uv_tcp_connect(connect_req, socket, (const struct sockaddr*) res->ai_addr, on_connect);

    uv_freeaddrinfo(res);
}
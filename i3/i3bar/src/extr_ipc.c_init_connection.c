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
typedef  int /*<<< orphan*/  ev_io ;

/* Variables and functions */
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  ev_io_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_io_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  got_data ; 
 int /*<<< orphan*/  i3_connection ; 
 int ipc_connect (char const*) ; 
 int /*<<< orphan*/  main_loop ; 
 int /*<<< orphan*/  smalloc (int) ; 
 char const* sock_path ; 

int init_connection(const char *socket_path) {
    sock_path = socket_path;
    int sockfd = ipc_connect(socket_path);
    i3_connection = smalloc(sizeof(ev_io));
    ev_io_init(i3_connection, &got_data, sockfd, EV_READ);
    ev_io_start(main_loop, i3_connection);
    return 1;
}
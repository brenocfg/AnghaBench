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

/* Variables and functions */
 int /*<<< orphan*/  uc_client_exit (int) ; 
 int uc_client_fork () ; 
 int uc_client_wait () ; 
 int /*<<< orphan*/  uc_socket_close (int) ; 
 int uc_socket_create () ; 

int
t_generic(int (*client_func)(int), int (*server_func)(int))
{
	int fd, rv, rv_client;

	switch (uc_client_fork()) {
	case 0:
		fd = uc_socket_create();
		if (fd < 0)
			rv = -2;
		else {
			rv = client_func(fd);
			if (uc_socket_close(fd) < 0)
				rv = -2;
		}
		uc_client_exit(rv);
		break;
	case 1:
		fd = uc_socket_create();
		if (fd < 0)
			rv = -2;
		else {
			rv = server_func(fd);
			rv_client = uc_client_wait();
			if (rv == 0 || (rv == -2 && rv_client != 0))
				rv = rv_client;
			if (uc_socket_close(fd) < 0)
				rv = -2;
		}
		break;
	default:
		rv = -2;
	}
	return (rv);
}
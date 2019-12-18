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
typedef  int /*<<< orphan*/  rk_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  accept (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ rk_IS_BAD_SOCKET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_closesocket (int /*<<< orphan*/ ) ; 
 int socket_to_fd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
accept_it (rk_socket_t s, rk_socket_t *ret_socket)
{
    rk_socket_t as;

    as = accept(s, NULL, NULL);
    if(rk_IS_BAD_SOCKET(as))
	err (1, "accept");

    if (ret_socket) {

	*ret_socket = as;

    } else {
	int fd = socket_to_fd(as, 0);

	/* We would use _O_RDONLY for the socket_to_fd() call for
	   STDIN, but there are instances where we assume that STDIN
	   is a r/w socket. */

	dup2(fd, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);

	rk_closesocket(as);
    }
}
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
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ socket_listen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int*,char*,char*,char*,char*) ; 
 int somaxconn ; 

__attribute__((used)) static void
test_defaults(void)
{
	int sock;

	/*
	 * First pass.  Confirm the default is 0.  Listen with a backlog of
	 * 0 and confirm it gets set that way.
	 */
	if (socket_listen(PF_INET, SOCK_STREAM, 0, 0, 0, 0, &sock, "PF_INET",
	    "SOCK_STREAM", "test_defaults", "default_0_listen_0") < 0)
		exit(-1);
	close(sock);

	/*
	 * Second pass.  Listen with a backlog of -1 and make sure it is set
	 * to somaxconn.
	 */
	if (socket_listen(PF_INET, SOCK_STREAM, 0, -1, 0, somaxconn, &sock,
	    "PF_INET", "SOCK_STREAM", "test_defaults", "default_0_listen_-1")
	    < 0)
		exit(-1);
	close(sock);

	/*
	 * Third pass.  Listen with a backlog of 1 and make sure it is set to
	 * 1.
	 */
	if (socket_listen(PF_INET, SOCK_STREAM, 0, 1, 0, 1, &sock, "PF_INET",
	    "SOCK_STREAM", "test_defaults", "default_0_listen_1") < 0)
		exit(-1);
	close(sock);

	/*
	 * Fourth pass.  Listen with a backlog of somaxconn and make sure it
	 * is set to somaxconn.
	 */
	if (socket_listen(PF_INET, SOCK_STREAM, 0, somaxconn, 0, somaxconn,
	    &sock, "PF_INET", "SOCK_STREAM", "test_defaults",
	    "default_0_listen_somaxconn") < 0)
		exit(-1);
	close(sock);

	/*
	 * Fifth pass.  Listen with a backlog of somaxconn+1 and make sure it
	 * is set to somaxconn.
	 */
	if (socket_listen(PF_INET, SOCK_STREAM, 0, somaxconn+1, 0, somaxconn,
	    &sock, "PF_INET", "SOCK_STREAM", "test_defaults",
	    "default_0_listen_somaxconn+1") < 0)
		exit(-1);
	close(sock);
}
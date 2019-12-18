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
typedef  int /*<<< orphan*/  uid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  geteuid () ; 
 scalar_t__ getuid () ; 
 scalar_t__ seteuid (int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_socket_priv(int type)
{
	uid_t olduid;
	int sock;

	if (getuid() != 0)
		errx(-1, "get_sock_priv: running without real uid 0");
	
	olduid = geteuid();
	if (seteuid(0) < 0)
		err(-1, "get_sock_priv: seteuid(0)");

	sock = socket(PF_INET, type, 0);

	if (seteuid(olduid) < 0)
		err(-1, "get_sock_priv: seteuid(%d)", olduid);

	return (sock);
}
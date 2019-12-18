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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct passwd {scalar_t__ pw_uid; } ;

/* Variables and functions */
 scalar_t__ ARG_MAX ; 
 scalar_t__ USERNAME_SZ ; 
 int /*<<< orphan*/  fatal (int,int /*<<< orphan*/ *,char*) ; 
 struct passwd* getpwnam (char*) ; 
 scalar_t__ iruserok (int /*<<< orphan*/ ,int,char*,char*) ; 
 char* read_str (int,scalar_t__,char*) ; 

__attribute__((used)) static int
recv_bsd_auth (int s, u_char *buf,
	       struct sockaddr_in *thisaddr,
	       struct sockaddr_in *thataddr,
	       char **client_username,
	       char **server_username,
	       char **cmd)
{
    struct passwd *pwd;

    *client_username = read_str (s, USERNAME_SZ, "local username");
    *server_username = read_str (s, USERNAME_SZ, "remote username");
    *cmd = read_str (s, ARG_MAX + 1, "command");
    pwd = getpwnam(*server_username);
    if (pwd == NULL)
	fatal(s, NULL, "Login incorrect.");
    if (iruserok(thataddr->sin_addr.s_addr, pwd->pw_uid == 0,
		 *client_username, *server_username))
	fatal(s, NULL, "Login incorrect.");
    return 0;
}
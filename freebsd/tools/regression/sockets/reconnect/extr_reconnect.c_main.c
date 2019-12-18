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
 int /*<<< orphan*/  PF_LOCAL ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  connect_uds_server (int,int /*<<< orphan*/ ) ; 
 int create_uds_server (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int mkstemp (int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uds_name1 ; 
 int /*<<< orphan*/  uds_name2 ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

int
main(void)
{
    int s_sock1, s_sock2, c_sock;

    atexit(cleanup);

    if (mkstemp(uds_name1) == -1)
	err(1, "mkstemp");
    unlink(uds_name1);
    s_sock1 = create_uds_server(uds_name1);

    if (mkstemp(uds_name2) == -1)
        err(1, "mkstemp");
    unlink(uds_name2);
    s_sock2 = create_uds_server(uds_name2);

    c_sock = socket(PF_LOCAL, SOCK_DGRAM, 0);
    if (c_sock < 0)
        err(1, "can't create socket");

    connect_uds_server(c_sock, uds_name1);
    close(s_sock1);
    connect_uds_server(c_sock, uds_name2);
    close(s_sock2);

    exit (0);
}
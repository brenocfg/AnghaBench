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
struct sockaddr_un {int /*<<< orphan*/  sun_path; } ;
typedef  int /*<<< orphan*/  sock ;
typedef  int /*<<< orphan*/  ifsun ;

/* Variables and functions */
 int /*<<< orphan*/  PF_LOCAL ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ bind (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  prepare_ifsun (struct sockaddr_un*,char const*) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sstosa (struct sockaddr_un*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
create_uds_server(const char *path)
{
    struct sockaddr_un ifsun;
    int sock;

    prepare_ifsun(&ifsun, path);

    unlink(ifsun.sun_path);

    sock = socket(PF_LOCAL, SOCK_DGRAM, 0);
    if (sock == -1)
        err(1, "can't create socket");
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &sock, sizeof(sock));
    if (bind(sock, sstosa(&ifsun), sizeof(ifsun)) < 0)
        err(1, "can't bind to a socket");

    return sock;
}
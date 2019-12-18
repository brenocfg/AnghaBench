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
struct sockaddr_un {int dummy; } ;
typedef  int /*<<< orphan*/  ifsun ;

/* Variables and functions */
 int connect (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  prepare_ifsun (struct sockaddr_un*,char const*) ; 
 int /*<<< orphan*/  sstosa (struct sockaddr_un*) ; 

__attribute__((used)) static void
connect_uds_server(int sock, const char *path)
{
    struct sockaddr_un ifsun;
    int e;

    prepare_ifsun(&ifsun, path);

    e = connect(sock, sstosa(&ifsun), sizeof(ifsun));
    if (e < 0)
        err(1, "can't connect to a socket");
}
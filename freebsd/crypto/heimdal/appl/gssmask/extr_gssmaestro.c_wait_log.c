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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct client {int salen; int /*<<< orphan*/  moniker; TYPE_1__* sa; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sast ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  sa_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOMAXCONN ; 
 int accept (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  eSetLoggingSocket ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int getsockname (int,struct sockaddr*,int*) ; 
 scalar_t__ listen (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put32 (struct client*,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_get_port (struct sockaddr*) ; 

__attribute__((used)) static int
wait_log(struct client *c)
{
    int32_t port;
    struct sockaddr_storage sast;
    socklen_t salen = sizeof(sast);
    int fd, fd2, ret;

    memset(&sast, 0, sizeof(sast));

    assert(sizeof(sast) >= c->salen);

    fd = socket(c->sa->sa_family, SOCK_STREAM, 0);
    if (fd < 0)
	err(1, "failed to build socket for %s's logging port", c->moniker);

    ((struct sockaddr *)&sast)->sa_family = c->sa->sa_family;
    ret = bind(fd, (struct sockaddr *)&sast, c->salen);
    if (ret < 0)
	err(1, "failed to bind %s's logging port", c->moniker);

    if (listen(fd, SOMAXCONN) < 0)
	err(1, "failed to listen %s's logging port", c->moniker);

    salen = sizeof(sast);
    ret = getsockname(fd, (struct sockaddr *)&sast, &salen);
    if (ret < 0)
	err(1, "failed to get address of local socket for %s", c->moniker);

    port = socket_get_port((struct sockaddr *)&sast);

    put32(c, eSetLoggingSocket);
    put32(c, ntohs(port));

    salen = sizeof(sast);
    fd2 = accept(fd, (struct sockaddr *)&sast, &salen);
    if (fd2 < 0)
	err(1, "failed to accept local socket for %s", c->moniker);
    close(fd);

    return fd2;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sa ;
struct TYPE_8__ {char const* path; } ;
struct TYPE_9__ {int flags; int /*<<< orphan*/  fd; struct timeval const* timeout; TYPE_1__ unix_sock; int /*<<< orphan*/  connection_type; } ;
typedef  TYPE_2__ redisContext ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 scalar_t__ EINPROGRESS ; 
 int REDIS_BLOCK ; 
 int REDIS_CONNECTED ; 
 int /*<<< orphan*/  REDIS_CONN_UNIX ; 
 int REDIS_ERR ; 
 scalar_t__ REDIS_OK ; 
 int connect (int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (struct timeval const*) ; 
 struct timeval const* malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct timeval const*,struct timeval const*,int) ; 
 scalar_t__ redisContextTimeoutMsec (TYPE_2__*,long*) ; 
 scalar_t__ redisContextWaitReady (TYPE_2__*,long) ; 
 scalar_t__ redisCreateSocket (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ redisSetBlocking (TYPE_2__*,int) ; 
 char const* strdup (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

int redisContextConnectUnix(redisContext *c, const char *path, const struct timeval *timeout) {
    int blocking = (c->flags & REDIS_BLOCK);
    struct sockaddr_un sa;
    long timeout_msec = -1;

    if (redisCreateSocket(c,AF_LOCAL) < 0)
        return REDIS_ERR;
    if (redisSetBlocking(c,0) != REDIS_OK)
        return REDIS_ERR;

    c->connection_type = REDIS_CONN_UNIX;
    if (c->unix_sock.path != path)
        c->unix_sock.path = strdup(path);

    if (timeout) {
        if (c->timeout != timeout) {
            if (c->timeout == NULL)
                c->timeout = malloc(sizeof(struct timeval));

            memcpy(c->timeout, timeout, sizeof(struct timeval));
        }
    } else {
        if (c->timeout)
            free(c->timeout);
        c->timeout = NULL;
    }

    if (redisContextTimeoutMsec(c,&timeout_msec) != REDIS_OK)
        return REDIS_ERR;

    sa.sun_family = AF_LOCAL;
    strncpy(sa.sun_path,path,sizeof(sa.sun_path)-1);
    if (connect(c->fd, (struct sockaddr*)&sa, sizeof(sa)) == -1) {
        if (errno == EINPROGRESS && !blocking) {
            /* This is ok. */
        } else {
            if (redisContextWaitReady(c,timeout_msec) != REDIS_OK)
                return REDIS_ERR;
        }
    }

    /* Reset socket to be blocking after connect(2). */
    if (blocking && redisSetBlocking(c,1) != REDIS_OK)
        return REDIS_ERR;

    c->flags |= REDIS_CONNECTED;
    return REDIS_OK;
}
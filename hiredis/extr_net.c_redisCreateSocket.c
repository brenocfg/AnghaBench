#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  redisFD ;
struct TYPE_5__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ redisContext ;

/* Variables and functions */
 int AF_INET ; 
 int REDIS_ERR ; 
 int /*<<< orphan*/  REDIS_ERR_IO ; 
 int /*<<< orphan*/  REDIS_INVALID_FD ; 
 int REDIS_OK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  __redisSetErrorFromErrno (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int redisSetReuseAddr (TYPE_1__*) ; 
 int /*<<< orphan*/  socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int redisCreateSocket(redisContext *c, int type) {
    redisFD s;
    if ((s = socket(type, SOCK_STREAM, 0)) == REDIS_INVALID_FD) {
        __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
        return REDIS_ERR;
    }
    c->fd = s;
    if (type == AF_INET) {
        if (redisSetReuseAddr(c) == REDIS_ERR) {
            return REDIS_ERR;
        }
    }
    return REDIS_OK;
}
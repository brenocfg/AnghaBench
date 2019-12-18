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
struct timeval {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ redisContext ;

/* Variables and functions */
 int /*<<< orphan*/  REDIS_BLOCK ; 
 int /*<<< orphan*/  redisContextConnectUnix (TYPE_1__*,char const*,struct timeval const*) ; 
 TYPE_1__* redisContextInit () ; 

redisContext *redisConnectUnixWithTimeout(const char *path, const struct timeval tv) {
    redisContext *c;

    c = redisContextInit();
    if (c == NULL)
        return NULL;

    c->flags |= REDIS_BLOCK;
    redisContextConnectUnix(c,path,&tv);
    return c;
}
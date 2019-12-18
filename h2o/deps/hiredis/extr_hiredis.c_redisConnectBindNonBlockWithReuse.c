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
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ redisContext ;

/* Variables and functions */
 int /*<<< orphan*/  REDIS_BLOCK ; 
 int /*<<< orphan*/  REDIS_REUSEADDR ; 
 int /*<<< orphan*/  redisContextConnectBindTcp (TYPE_1__*,char const*,int,int /*<<< orphan*/ *,char const*) ; 
 TYPE_1__* redisContextInit () ; 

redisContext *redisConnectBindNonBlockWithReuse(const char *ip, int port,
                                                const char *source_addr) {
    redisContext *c = redisContextInit();
    c->flags &= ~REDIS_BLOCK;
    c->flags |= REDIS_REUSEADDR;
    redisContextConnectBindTcp(c,ip,port,NULL,source_addr);
    return c;
}
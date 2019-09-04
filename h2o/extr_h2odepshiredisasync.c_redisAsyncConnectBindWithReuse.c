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
typedef  int /*<<< orphan*/  redisContext ;
typedef  int /*<<< orphan*/  redisAsyncContext ;

/* Variables and functions */
 int /*<<< orphan*/  __redisAsyncCopyError (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * redisAsyncInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * redisConnectBindNonBlockWithReuse (char const*,int,char const*) ; 

redisAsyncContext *redisAsyncConnectBindWithReuse(const char *ip, int port,
                                                  const char *source_addr) {
    redisContext *c = redisConnectBindNonBlockWithReuse(ip,port,source_addr);
    redisAsyncContext *ac = redisAsyncInitialize(c);
    __redisAsyncCopyError(ac);
    return ac;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int tv_sec; int tv_usec; } ;
struct TYPE_6__ {TYPE_5__ timeout; int /*<<< orphan*/  port; int /*<<< orphan*/  host; } ;
struct config {TYPE_1__ tcp; } ;
struct TYPE_7__ {scalar_t__ err; int /*<<< orphan*/  errstr; } ;
typedef  TYPE_2__ redisContext ;
typedef  int LONG_MAX ;

/* Variables and functions */
 scalar_t__ REDIS_ERR_IO ; 
 TYPE_2__* redisConnectWithTimeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__) ; 
 int /*<<< orphan*/  redisFree (TYPE_2__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test (char*) ; 
 int /*<<< orphan*/  test_cond (int) ; 

__attribute__((used)) static void test_invalid_timeout_errors(struct config config) {
    redisContext *c;

    test("Set error when an invalid timeout usec value is given to redisConnectWithTimeout: ");

    config.tcp.timeout.tv_sec = 0;
    config.tcp.timeout.tv_usec = 10000001;

    c = redisConnectWithTimeout(config.tcp.host, config.tcp.port, config.tcp.timeout);

    test_cond(c->err == REDIS_ERR_IO && strcmp(c->errstr, "Invalid timeout specified") == 0);
    redisFree(c);

    test("Set error when an invalid timeout sec value is given to redisConnectWithTimeout: ");

    config.tcp.timeout.tv_sec = (((LONG_MAX) - 999) / 1000) + 1;
    config.tcp.timeout.tv_usec = 0;

    c = redisConnectWithTimeout(config.tcp.host, config.tcp.port, config.tcp.timeout);

    test_cond(c->err == REDIS_ERR_IO && strcmp(c->errstr, "Invalid timeout specified") == 0);
    redisFree(c);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  redisFD ;
struct TYPE_4__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ redisContext ;

/* Variables and functions */
 int /*<<< orphan*/  REDIS_INVALID_FD ; 
 int /*<<< orphan*/  redisFree (TYPE_1__*) ; 

redisFD redisFreeKeepFd(redisContext *c) {
    redisFD fd = c->fd;
    c->fd = REDIS_INVALID_FD;
    redisFree(c);
    return fd;
}
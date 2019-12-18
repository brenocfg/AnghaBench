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
typedef  int /*<<< orphan*/  redisReply ;
typedef  int /*<<< orphan*/  redisContext ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeReplyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * redisCommand (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  redisFree (int /*<<< orphan*/ *) ; 
 int redisFreeKeepFd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int disconnect(redisContext *c, int keep_fd) {
    redisReply *reply;

    /* Make sure we're on DB 9. */
    reply = redisCommand(c,"SELECT 9");
    assert(reply != NULL);
    freeReplyObject(reply);
    reply = redisCommand(c,"FLUSHDB");
    assert(reply != NULL);
    freeReplyObject(reply);

    /* Free the context as well, but keep the fd if requested. */
    if (keep_fd)
        return redisFreeKeepFd(c);
    redisFree(c);
    return -1;
}
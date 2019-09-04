#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_13__ {char* path; } ;
struct TYPE_12__ {char* host; } ;
struct config {TYPE_2__ unix_sock; TYPE_1__ tcp; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_14__ {scalar_t__ type; int /*<<< orphan*/  str; } ;
typedef  TYPE_3__ redisReply ;
struct TYPE_15__ {scalar_t__ err; int /*<<< orphan*/  errstr; int /*<<< orphan*/  fd; } ;
typedef  TYPE_4__ redisContext ;

/* Variables and functions */
 scalar_t__ REDIS_ERR_IO ; 
 scalar_t__ REDIS_REPLY_STATUS ; 
 scalar_t__ REDIS_REPLY_STRING ; 
 TYPE_4__* connect (struct config) ; 
 int /*<<< orphan*/  disconnect (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeReplyObject (TYPE_3__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_3__* redisCommand (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  redisReconnect (TYPE_4__*) ; 
 int /*<<< orphan*/  redisSetTimeout (TYPE_4__*,struct timeval) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  test (char*) ; 
 int /*<<< orphan*/  test_cond (int) ; 
 scalar_t__ write (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_blocking_connection_timeouts(struct config config) {
    redisContext *c;
    redisReply *reply;
    ssize_t s;
    const char *cmd = "DEBUG SLEEP 3\r\n";
    struct timeval tv;

    c = connect(config);
    test("Successfully completes a command when the timeout is not exceeded: ");
    reply = redisCommand(c,"SET foo fast");
    freeReplyObject(reply);
    tv.tv_sec = 0;
    tv.tv_usec = 10000;
    redisSetTimeout(c, tv);
    reply = redisCommand(c, "GET foo");
    test_cond(reply != NULL && reply->type == REDIS_REPLY_STRING && memcmp(reply->str, "fast", 4) == 0);
    freeReplyObject(reply);
    disconnect(c, 0);

    c = connect(config);
    test("Does not return a reply when the command times out: ");
    s = write(c->fd, cmd, strlen(cmd));
    tv.tv_sec = 0;
    tv.tv_usec = 10000;
    redisSetTimeout(c, tv);
    reply = redisCommand(c, "GET foo");
    test_cond(s > 0 && reply == NULL && c->err == REDIS_ERR_IO && strcmp(c->errstr, "Resource temporarily unavailable") == 0);
    freeReplyObject(reply);

    test("Reconnect properly reconnects after a timeout: ");
    redisReconnect(c);
    reply = redisCommand(c, "PING");
    test_cond(reply != NULL && reply->type == REDIS_REPLY_STATUS && strcmp(reply->str, "PONG") == 0);
    freeReplyObject(reply);

    test("Reconnect properly uses owned parameters: ");
    config.tcp.host = "foo";
    config.unix_sock.path = "foo";
    redisReconnect(c);
    reply = redisCommand(c, "PING");
    test_cond(reply != NULL && reply->type == REDIS_REPLY_STATUS && strcmp(reply->str, "PONG") == 0);
    freeReplyObject(reply);

    disconnect(c, 0);
}
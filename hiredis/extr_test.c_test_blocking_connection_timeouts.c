#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_17__ {char* path; } ;
struct TYPE_16__ {char* host; } ;
struct config {TYPE_3__ unix_sock; TYPE_2__ tcp; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_18__ {scalar_t__ type; int /*<<< orphan*/  str; } ;
typedef  TYPE_4__ redisReply ;
struct TYPE_19__ {scalar_t__ err; int /*<<< orphan*/  errstr; TYPE_1__* funcs; } ;
typedef  TYPE_5__ redisContext ;
struct TYPE_15__ {scalar_t__ (* write ) (TYPE_5__*) ;} ;

/* Variables and functions */
 scalar_t__ REDIS_ERR_IO ; 
 scalar_t__ REDIS_REPLY_STATUS ; 
 scalar_t__ REDIS_REPLY_STRING ; 
 int /*<<< orphan*/  disconnect (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* do_connect (struct config) ; 
 int /*<<< orphan*/  do_reconnect (TYPE_5__*,struct config) ; 
 int /*<<< orphan*/  freeReplyObject (TYPE_4__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  redisAppendFormattedCommand (TYPE_5__*,char const*,int /*<<< orphan*/ ) ; 
 TYPE_4__* redisCommand (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  redisSetTimeout (TYPE_5__*,struct timeval) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ stub1 (TYPE_5__*) ; 
 int /*<<< orphan*/  test (char*) ; 
 int /*<<< orphan*/  test_cond (int) ; 

__attribute__((used)) static void test_blocking_connection_timeouts(struct config config) {
    redisContext *c;
    redisReply *reply;
    ssize_t s;
    const char *cmd = "DEBUG SLEEP 3\r\n";
    struct timeval tv;

    c = do_connect(config);
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

    c = do_connect(config);
    test("Does not return a reply when the command times out: ");
    redisAppendFormattedCommand(c, cmd, strlen(cmd));
    s = c->funcs->write(c);
    tv.tv_sec = 0;
    tv.tv_usec = 10000;
    redisSetTimeout(c, tv);
    reply = redisCommand(c, "GET foo");
    test_cond(s > 0 && reply == NULL && c->err == REDIS_ERR_IO && strcmp(c->errstr, "Resource temporarily unavailable") == 0);
    freeReplyObject(reply);

    test("Reconnect properly reconnects after a timeout: ");
    do_reconnect(c, config);
    reply = redisCommand(c, "PING");
    test_cond(reply != NULL && reply->type == REDIS_REPLY_STATUS && strcmp(reply->str, "PONG") == 0);
    freeReplyObject(reply);

    test("Reconnect properly uses owned parameters: ");
    config.tcp.host = "foo";
    config.unix_sock.path = "foo";
    do_reconnect(c, config);
    reply = redisCommand(c, "PING");
    test_cond(reply != NULL && reply->type == REDIS_REPLY_STATUS && strcmp(reply->str, "PONG") == 0);
    freeReplyObject(reply);

    disconnect(c, 0);
}
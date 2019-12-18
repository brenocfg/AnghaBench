#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct timeval {int member_1; int /*<<< orphan*/  member_0; } ;
struct config {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ redisReply ;
struct TYPE_11__ {scalar_t__ err; int /*<<< orphan*/  errstr; } ;
typedef  TYPE_2__ redisContext ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ REDIS_ERR ; 
 scalar_t__ REDIS_ERR_EOF ; 
 scalar_t__ REDIS_ERR_IO ; 
 scalar_t__ REDIS_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* connect (struct config) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  freeReplyObject (TYPE_1__*) ; 
 TYPE_1__* redisCommand (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  redisFree (TYPE_2__*) ; 
 scalar_t__ redisGetReply (TYPE_2__*,void**) ; 
 scalar_t__ redisSetTimeout (TYPE_2__*,struct timeval) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int strlen (char const*) ; 
 char* strstr (int /*<<< orphan*/ ,char const*) ; 
 int strtol (char*,char**,int) ; 
 int /*<<< orphan*/  test (char*) ; 
 int /*<<< orphan*/  test_cond (int) ; 

__attribute__((used)) static void test_blocking_io_errors(struct config config) {
    redisContext *c;
    redisReply *reply;
    void *_reply;
    int major, minor;

    /* Connect to target given by config. */
    c = connect(config);
    {
        /* Find out Redis version to determine the path for the next test */
        const char *field = "redis_version:";
        char *p, *eptr;

        reply = redisCommand(c,"INFO");
        p = strstr(reply->str,field);
        major = strtol(p+strlen(field),&eptr,10);
        p = eptr+1; /* char next to the first "." */
        minor = strtol(p,&eptr,10);
        freeReplyObject(reply);
    }

    test("Returns I/O error when the connection is lost: ");
    reply = redisCommand(c,"QUIT");
    if (major > 2 || (major == 2 && minor > 0)) {
        /* > 2.0 returns OK on QUIT and read() should be issued once more
         * to know the descriptor is at EOF. */
        test_cond(strcasecmp(reply->str,"OK") == 0 &&
            redisGetReply(c,&_reply) == REDIS_ERR);
        freeReplyObject(reply);
    } else {
        test_cond(reply == NULL);
    }

    /* On 2.0, QUIT will cause the connection to be closed immediately and
     * the read(2) for the reply on QUIT will set the error to EOF.
     * On >2.0, QUIT will return with OK and another read(2) needed to be
     * issued to find out the socket was closed by the server. In both
     * conditions, the error will be set to EOF. */
    assert(c->err == REDIS_ERR_EOF &&
        strcmp(c->errstr,"Server closed the connection") == 0);
    redisFree(c);

    c = connect(config);
    test("Returns I/O error on socket timeout: ");
    struct timeval tv = { 0, 1000 };
    assert(redisSetTimeout(c,tv) == REDIS_OK);
    test_cond(redisGetReply(c,&_reply) == REDIS_ERR &&
        c->err == REDIS_ERR_IO && errno == EAGAIN);
    redisFree(c);
}
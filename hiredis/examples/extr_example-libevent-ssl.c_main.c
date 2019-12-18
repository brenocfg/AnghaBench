#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct event_base {int dummy; } ;
struct TYPE_7__ {char* errstr; int /*<<< orphan*/  c; scalar_t__ err; } ;
typedef  TYPE_1__ redisAsyncContext ;

/* Variables and functions */
 scalar_t__ REDIS_OK ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  connectCallback ; 
 int /*<<< orphan*/  disconnectCallback ; 
 int /*<<< orphan*/  event_base_dispatch (struct event_base*) ; 
 struct event_base* event_base_new () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  getCallback ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  redisAsyncCommand (TYPE_1__*,int /*<<< orphan*/ ,char*,char*,...) ; 
 TYPE_1__* redisAsyncConnect (char const*,int) ; 
 int /*<<< orphan*/  redisAsyncSetConnectCallback (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redisAsyncSetDisconnectCallback (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redisLibeventAttach (TYPE_1__*,struct event_base*) ; 
 scalar_t__ redisSecureConnection (int /*<<< orphan*/ *,char const*,char const*,char const*,char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 size_t strlen (char const*) ; 

int main (int argc, char **argv) {
    signal(SIGPIPE, SIG_IGN);
    struct event_base *base = event_base_new();
    if (argc < 5) {
        fprintf(stderr,
                "Usage: %s <key> <host> <port> <cert> <certKey> [ca]\n", argv[0]);
        exit(1);
    }

    const char *value = argv[1];
    size_t nvalue = strlen(value);

    const char *hostname = argv[2];
    int port = atoi(argv[3]);

    const char *cert = argv[4];
    const char *certKey = argv[5];
    const char *caCert = argc > 5 ? argv[6] : NULL;

    redisAsyncContext *c = redisAsyncConnect(hostname, port);
    if (c->err) {
        /* Let *c leak for now... */
        printf("Error: %s\n", c->errstr);
        return 1;
    }
    if (redisSecureConnection(&c->c, caCert, cert, certKey, "sni") != REDIS_OK) {
        printf("SSL Error!\n");
        exit(1);
    }

    redisLibeventAttach(c,base);
    redisAsyncSetConnectCallback(c,connectCallback);
    redisAsyncSetDisconnectCallback(c,disconnectCallback);
    redisAsyncCommand(c, NULL, NULL, "SET key %b", value, nvalue);
    redisAsyncCommand(c, getCallback, (char*)"end-1", "GET key");
    event_base_dispatch(base);
    return 0;
}
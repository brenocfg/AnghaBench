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
struct TYPE_7__ {char* errstr; scalar_t__ err; } ;
typedef  TYPE_1__ redisAsyncContext ;

/* Variables and functions */
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  connectCallback ; 
 int /*<<< orphan*/  disconnectCallback ; 
 int /*<<< orphan*/  getCallback ; 
 int /*<<< orphan*/  iv_deinit () ; 
 int /*<<< orphan*/  iv_init () ; 
 int /*<<< orphan*/  iv_main () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  redisAsyncCommand (TYPE_1__*,int /*<<< orphan*/ ,char*,char*,...) ; 
 TYPE_1__* redisAsyncConnect (char*,int) ; 
 int /*<<< orphan*/  redisAsyncSetConnectCallback (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redisAsyncSetDisconnectCallback (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redisIvykisAttach (TYPE_1__*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int main (int argc, char **argv) {
    signal(SIGPIPE, SIG_IGN);

    iv_init();

    redisAsyncContext *c = redisAsyncConnect("127.0.0.1", 6379);
    if (c->err) {
        /* Let *c leak for now... */
        printf("Error: %s\n", c->errstr);
        return 1;
    }

    redisIvykisAttach(c);
    redisAsyncSetConnectCallback(c,connectCallback);
    redisAsyncSetDisconnectCallback(c,disconnectCallback);
    redisAsyncCommand(c, NULL, NULL, "SET key %b", argv[argc-1], strlen(argv[argc-1]));
    redisAsyncCommand(c, getCallback, (char*)"end-1", "GET key");

    iv_main();

    iv_deinit();

    return 0;
}
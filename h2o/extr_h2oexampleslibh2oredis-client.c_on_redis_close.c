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

/* Variables and functions */
 int /*<<< orphan*/  client ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  h2o_redis_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void on_redis_close(const char *errstr)
{
    if (errstr == NULL) {
        fprintf(stderr, "disconnected from redis\n");
    } else {
        fprintf(stderr, "redis connection failure: %s\n", errstr);
        /* try to reconnect after 1 second */
        usleep(1000000);
        h2o_redis_connect(client, host, port);
    }
}
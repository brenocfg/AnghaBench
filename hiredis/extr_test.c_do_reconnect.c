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
struct config {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  redisContext ;

/* Variables and functions */
 scalar_t__ CONN_SSL ; 
 int /*<<< orphan*/  do_ssl_handshake (int /*<<< orphan*/ *,struct config) ; 
 int /*<<< orphan*/  redisReconnect (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_reconnect(redisContext *c, struct config config) {
    redisReconnect(c);

    if (config.type == CONN_SSL) {
        do_ssl_handshake(c, config);
    }
}
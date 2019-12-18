#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* path; } ;
struct TYPE_11__ {TYPE_4__* source_addr; TYPE_4__* host; } ;
struct TYPE_12__ {int /*<<< orphan*/  privdata; TYPE_2__* funcs; struct TYPE_12__* saddr; struct TYPE_12__* timeout; TYPE_1__ unix_sock; TYPE_3__ tcp; int /*<<< orphan*/  reader; int /*<<< orphan*/  obuf; } ;
typedef  TYPE_4__ redisContext ;
struct TYPE_10__ {int /*<<< orphan*/  (* free_privdata ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  redisNetClose (TYPE_4__*) ; 
 int /*<<< orphan*/  redisReaderFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void redisFree(redisContext *c) {
    if (c == NULL)
        return;
    redisNetClose(c);

    sdsfree(c->obuf);
    redisReaderFree(c->reader);
    free(c->tcp.host);
    free(c->tcp.source_addr);
    free(c->unix_sock.path);
    free(c->timeout);
    free(c->saddr);
    if (c->funcs->free_privdata) {
        c->funcs->free_privdata(c->privdata);
    }
    memset(c, 0xff, sizeof(*c));
    free(c);
}
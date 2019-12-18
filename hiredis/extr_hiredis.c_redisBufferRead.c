#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* reader; TYPE_1__* funcs; scalar_t__ err; } ;
typedef  TYPE_2__ redisContext ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_9__ {int /*<<< orphan*/  errstr; int /*<<< orphan*/  err; } ;
struct TYPE_7__ {int (* read ) (TYPE_2__*,char*,int) ;} ;

/* Variables and functions */
 int REDIS_ERR ; 
 scalar_t__ REDIS_OK ; 
 int /*<<< orphan*/  __redisSetError (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ redisReaderFeed (TYPE_4__*,char*,int) ; 
 int stub1 (TYPE_2__*,char*,int) ; 

int redisBufferRead(redisContext *c) {
    char buf[1024*16];
    int nread;

    /* Return early when the context has seen an error. */
    if (c->err)
        return REDIS_ERR;

    nread = c->funcs->read(c, buf, sizeof(buf));
    if (nread > 0) {
        if (redisReaderFeed(c->reader, buf, nread) != REDIS_OK) {
            __redisSetError(c, c->reader->err, c->reader->errstr);
            return REDIS_ERR;
        } else {
        }
    } else if (nread < 0) {
        return REDIS_ERR;
    }
    return REDIS_OK;
}
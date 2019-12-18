#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ssl_async_args {int dummy; } ;
struct TYPE_3__ {void* rwstate; int /*<<< orphan*/ * job; int /*<<< orphan*/ * waitctx; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
#define  ASYNC_ERR 131 
#define  ASYNC_FINISH 130 
#define  ASYNC_NO_JOBS 129 
#define  ASYNC_PAUSE 128 
 int /*<<< orphan*/ * ASYNC_WAIT_CTX_new () ; 
 int ASYNC_start_job (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*,int (*) (void*),struct ssl_async_args*,int) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 void* SSL_ASYNC_NO_JOBS ; 
 void* SSL_ASYNC_PAUSED ; 
 int /*<<< orphan*/  SSL_F_SSL_START_ASYNC_JOB ; 
 void* SSL_NOTHING ; 
 int /*<<< orphan*/  SSL_R_FAILED_TO_INIT_ASYNC ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssl_start_async_job(SSL *s, struct ssl_async_args *args,
                               int (*func) (void *))
{
    int ret;
    if (s->waitctx == NULL) {
        s->waitctx = ASYNC_WAIT_CTX_new();
        if (s->waitctx == NULL)
            return -1;
    }
    switch (ASYNC_start_job(&s->job, s->waitctx, &ret, func, args,
                            sizeof(struct ssl_async_args))) {
    case ASYNC_ERR:
        s->rwstate = SSL_NOTHING;
        SSLerr(SSL_F_SSL_START_ASYNC_JOB, SSL_R_FAILED_TO_INIT_ASYNC);
        return -1;
    case ASYNC_PAUSE:
        s->rwstate = SSL_ASYNC_PAUSED;
        return -1;
    case ASYNC_NO_JOBS:
        s->rwstate = SSL_ASYNC_NO_JOBS;
        return -1;
    case ASYNC_FINISH:
        s->job = NULL;
        return ret;
    default:
        s->rwstate = SSL_NOTHING;
        SSLerr(SSL_F_SSL_START_ASYNC_JOB, ERR_R_INTERNAL_ERROR);
        /* Shouldn't happen */
        return -1;
    }
}
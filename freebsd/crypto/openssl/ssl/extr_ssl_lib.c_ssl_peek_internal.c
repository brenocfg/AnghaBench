#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int (* func_read ) (TYPE_3__*,void*,size_t,size_t*) ;} ;
struct ssl_async_args {size_t num; TYPE_1__ f; int /*<<< orphan*/  type; void* buf; TYPE_3__* s; } ;
struct TYPE_9__ {int shutdown; int mode; size_t asyncrw; TYPE_2__* method; int /*<<< orphan*/ * handshake_func; } ;
struct TYPE_8__ {int (* ssl_peek ) (TYPE_3__*,void*,size_t,size_t*) ;} ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/ * ASYNC_get_current_job () ; 
 int /*<<< orphan*/  READFUNC ; 
 int /*<<< orphan*/  SSL_F_SSL_PEEK_INTERNAL ; 
 int SSL_MODE_ASYNC ; 
 int SSL_RECEIVED_SHUTDOWN ; 
 int /*<<< orphan*/  SSL_R_UNINITIALIZED ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_io_intern ; 
 int ssl_start_async_job (TYPE_3__*,struct ssl_async_args*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__*,void*,size_t,size_t*) ; 

__attribute__((used)) static int ssl_peek_internal(SSL *s, void *buf, size_t num, size_t *readbytes)
{
    if (s->handshake_func == NULL) {
        SSLerr(SSL_F_SSL_PEEK_INTERNAL, SSL_R_UNINITIALIZED);
        return -1;
    }

    if (s->shutdown & SSL_RECEIVED_SHUTDOWN) {
        return 0;
    }
    if ((s->mode & SSL_MODE_ASYNC) && ASYNC_get_current_job() == NULL) {
        struct ssl_async_args args;
        int ret;

        args.s = s;
        args.buf = buf;
        args.num = num;
        args.type = READFUNC;
        args.f.func_read = s->method->ssl_peek;

        ret = ssl_start_async_job(s, &args, ssl_io_intern);
        *readbytes = s->asyncrw;
        return ret;
    } else {
        return s->method->ssl_peek(s, buf, num, readbytes);
    }
}
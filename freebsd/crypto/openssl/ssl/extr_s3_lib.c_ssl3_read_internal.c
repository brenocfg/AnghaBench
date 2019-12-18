#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* s3; TYPE_1__* method; } ;
struct TYPE_10__ {int in_read_app_data; scalar_t__ renegotiate; } ;
struct TYPE_9__ {int (* ssl_read_bytes ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,size_t,int,size_t*) ;} ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL3_RT_APPLICATION_DATA ; 
 int /*<<< orphan*/  clear_sys_error () ; 
 int /*<<< orphan*/  ossl_statem_set_in_handshake (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ssl3_renegotiate_check (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,size_t,int,size_t*) ; 
 int stub2 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,size_t,int,size_t*) ; 

__attribute__((used)) static int ssl3_read_internal(SSL *s, void *buf, size_t len, int peek,
                              size_t *readbytes)
{
    int ret;

    clear_sys_error();
    if (s->s3->renegotiate)
        ssl3_renegotiate_check(s, 0);
    s->s3->in_read_app_data = 1;
    ret =
        s->method->ssl_read_bytes(s, SSL3_RT_APPLICATION_DATA, NULL, buf, len,
                                  peek, readbytes);
    if ((ret == -1) && (s->s3->in_read_app_data == 2)) {
        /*
         * ssl3_read_bytes decided to call s->handshake_func, which called
         * ssl3_read_bytes to read handshake data. However, ssl3_read_bytes
         * actually found application data and thinks that application data
         * makes sense here; so disable handshake processing and try to read
         * application data again.
         */
        ossl_statem_set_in_handshake(s, 1);
        ret =
            s->method->ssl_read_bytes(s, SSL3_RT_APPLICATION_DATA, NULL, buf,
                                      len, peek, readbytes);
        ossl_statem_set_in_handshake(s, 0);
    } else
        s->s3->in_read_app_data = 0;

    return ret;
}
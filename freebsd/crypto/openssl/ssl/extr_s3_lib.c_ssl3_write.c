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
struct TYPE_9__ {TYPE_2__* method; TYPE_1__* s3; } ;
struct TYPE_8__ {int (* ssl_write_bytes ) (TYPE_3__*,int /*<<< orphan*/ ,void const*,size_t,size_t*) ;} ;
struct TYPE_7__ {scalar_t__ renegotiate; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL3_RT_APPLICATION_DATA ; 
 int /*<<< orphan*/  clear_sys_error () ; 
 int /*<<< orphan*/  ssl3_renegotiate_check (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/ ,void const*,size_t,size_t*) ; 

int ssl3_write(SSL *s, const void *buf, size_t len, size_t *written)
{
    clear_sys_error();
    if (s->s3->renegotiate)
        ssl3_renegotiate_check(s, 0);

    return s->method->ssl_write_bytes(s, SSL3_RT_APPLICATION_DATA, buf, len,
                                      written);
}
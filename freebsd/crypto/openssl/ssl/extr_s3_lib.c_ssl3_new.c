#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* method; int /*<<< orphan*/ * s3; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* ssl_clear ) (TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  SSL3_STATE ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/ * OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  SSL_SRP_CTX_init (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

int ssl3_new(SSL *s)
{
    SSL3_STATE *s3;

    if ((s3 = OPENSSL_zalloc(sizeof(*s3))) == NULL)
        goto err;
    s->s3 = s3;

#ifndef OPENSSL_NO_SRP
    if (!SSL_SRP_CTX_init(s))
        goto err;
#endif

    if (!s->method->ssl_clear(s))
        return 0;

    return 1;
 err:
    return 0;
}
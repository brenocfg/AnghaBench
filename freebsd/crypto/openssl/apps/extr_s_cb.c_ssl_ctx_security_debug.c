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
struct TYPE_3__ {int verbose; int /*<<< orphan*/  old_cb; int /*<<< orphan*/  out; } ;
typedef  TYPE_1__ security_debug_ex ;
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_get_security_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set0_security_ex_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_CTX_set_security_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  security_callback_debug ; 

void ssl_ctx_security_debug(SSL_CTX *ctx, int verbose)
{
    static security_debug_ex sdb;

    sdb.out = bio_err;
    sdb.verbose = verbose;
    sdb.old_cb = SSL_CTX_get_security_callback(ctx);
    SSL_CTX_set_security_callback(ctx, security_callback_debug);
    SSL_CTX_set0_security_ex_data(ctx, &sdb);
}
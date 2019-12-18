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
struct TYPE_3__ {int /*<<< orphan*/  cert_store; } ;
typedef  TYPE_1__ SSL_CTX ;

/* Variables and functions */
 int X509_STORE_load_locations (int /*<<< orphan*/ ,char const*,char const*) ; 

int SSL_CTX_load_verify_locations(SSL_CTX *ctx, const char *CAfile,
                                  const char *CApath)
{
    return X509_STORE_load_locations(ctx->cert_store, CAfile, CApath);
}
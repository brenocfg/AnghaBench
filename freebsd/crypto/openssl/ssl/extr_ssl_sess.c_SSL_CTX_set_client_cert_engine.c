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
struct TYPE_3__ {int /*<<< orphan*/ * client_cert_engine; } ;
typedef  TYPE_1__ SSL_CTX ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_get_ssl_client_cert_function (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_ENGINE_LIB ; 
 int /*<<< orphan*/  SSL_F_SSL_CTX_SET_CLIENT_CERT_ENGINE ; 
 int /*<<< orphan*/  SSL_R_NO_CLIENT_CERT_METHOD ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int SSL_CTX_set_client_cert_engine(SSL_CTX *ctx, ENGINE *e)
{
    if (!ENGINE_init(e)) {
        SSLerr(SSL_F_SSL_CTX_SET_CLIENT_CERT_ENGINE, ERR_R_ENGINE_LIB);
        return 0;
    }
    if (!ENGINE_get_ssl_client_cert_function(e)) {
        SSLerr(SSL_F_SSL_CTX_SET_CLIENT_CERT_ENGINE,
               SSL_R_NO_CLIENT_CERT_METHOD);
        ENGINE_finish(e);
        return 0;
    }
    ctx->client_cert_engine = e;
    return 1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptls_iovec_t ;
struct TYPE_4__ {int /*<<< orphan*/  count; int /*<<< orphan*/ * list; } ;
struct TYPE_5__ {TYPE_1__ certificates; } ;
typedef  TYPE_2__ ptls_context_t ;

/* Variables and functions */
 int PTLS_ERROR_NO_MEMORY ; 
 int PTLS_MAX_CERTS_IN_CONTEXT ; 
 scalar_t__ malloc (int) ; 
 int ptls_load_pem_objects (char const*,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int ptls_load_certificates(ptls_context_t *ctx, char const *cert_pem_file)
{
    int ret = 0;

    ctx->certificates.list = (ptls_iovec_t *)malloc(PTLS_MAX_CERTS_IN_CONTEXT * sizeof(ptls_iovec_t));

    if (ctx->certificates.list == NULL) {
        ret = PTLS_ERROR_NO_MEMORY;
    } else {
        ret = ptls_load_pem_objects(cert_pem_file, "CERTIFICATE", ctx->certificates.list, PTLS_MAX_CERTS_IN_CONTEXT,
                                    &ctx->certificates.count);
    }

    return ret;
}
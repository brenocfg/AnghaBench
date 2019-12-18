#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  acceptor_subkey; scalar_t__ have_acceptor_subkey; int /*<<< orphan*/  ctx_key; } ;
struct TYPE_5__ {int /*<<< orphan*/  ctx_key; } ;
struct TYPE_7__ {int version; int protocol; TYPE_2__ cfx_kd; TYPE_1__ rfc1964_kd; } ;
typedef  TYPE_3__ gss_krb5_lucid_context_v1_t ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  free_key (int /*<<< orphan*/ *) ; 

OM_uint32
gss_krb5_free_lucid_sec_context(OM_uint32 *minor_status, void *c)
{
    gss_krb5_lucid_context_v1_t *ctx = c;

    if (ctx->version != 1) {
	if (minor_status)
	    *minor_status = 0;
	return GSS_S_FAILURE;
    }

    if (ctx->protocol == 0) {
	free_key(&ctx->rfc1964_kd.ctx_key);
    } else if (ctx->protocol == 1) {
	free_key(&ctx->cfx_kd.ctx_key);
	if (ctx->cfx_kd.have_acceptor_subkey)
	    free_key(&ctx->cfx_kd.acceptor_subkey);
    }
    free(ctx);
    if (minor_status)
	*minor_status = 0;
    return GSS_S_COMPLETE;
}
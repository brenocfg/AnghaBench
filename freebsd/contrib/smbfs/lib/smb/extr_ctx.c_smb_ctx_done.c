#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ ioc_local; scalar_t__ ioc_server; } ;
struct smb_ctx {scalar_t__ ct_nb; scalar_t__ ct_srvaddr; TYPE_1__ ct_ssn; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  nb_ctx_done (scalar_t__) ; 
 int /*<<< orphan*/  nb_snbfree (scalar_t__) ; 

void
smb_ctx_done(struct smb_ctx *ctx)
{
	if (ctx->ct_ssn.ioc_server)
		nb_snbfree(ctx->ct_ssn.ioc_server);
	if (ctx->ct_ssn.ioc_local)
		nb_snbfree(ctx->ct_ssn.ioc_local);
	if (ctx->ct_srvaddr)
		free(ctx->ct_srvaddr);
	if (ctx->ct_nb)
		nb_ctx_done(ctx->ct_nb);
}
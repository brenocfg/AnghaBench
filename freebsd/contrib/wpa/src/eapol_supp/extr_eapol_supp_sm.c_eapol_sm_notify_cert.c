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
struct tls_cert_data {int dummy; } ;
struct eapol_sm {TYPE_1__* ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* cert_cb ) (int /*<<< orphan*/ ,struct tls_cert_data*,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct tls_cert_data*,char const*) ; 

__attribute__((used)) static void eapol_sm_notify_cert(void *ctx, struct tls_cert_data *cert,
				 const char *cert_hash)
{
	struct eapol_sm *sm = ctx;
	if (sm->ctx->cert_cb)
		sm->ctx->cert_cb(sm->ctx->ctx, cert, cert_hash);
}
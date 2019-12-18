#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct krb5_context {int /*<<< orphan*/  kc_lock; } ;
typedef  scalar_t__ gss_ctx_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
krb5_init(gss_ctx_id_t ctx)
{
	struct krb5_context *kc = (struct krb5_context *)ctx;

	mtx_init(&kc->kc_lock, "krb5 gss lock", NULL, MTX_DEF);
}
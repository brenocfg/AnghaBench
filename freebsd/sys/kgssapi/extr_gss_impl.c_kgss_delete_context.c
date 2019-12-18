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
typedef  int /*<<< orphan*/  kobj_t ;
typedef  scalar_t__ gss_ctx_id_t ;
typedef  int /*<<< orphan*/  gss_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  KGSS_DELETE (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_GSSAPI ; 
 int /*<<< orphan*/  kobj_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
kgss_delete_context(gss_ctx_id_t ctx, gss_buffer_t output_token)
{

	KGSS_DELETE(ctx, output_token);
	kobj_delete((kobj_t) ctx, M_GSSAPI);
}
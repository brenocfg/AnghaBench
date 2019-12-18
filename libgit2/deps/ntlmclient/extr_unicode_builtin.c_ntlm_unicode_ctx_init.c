#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ntlm; } ;
typedef  TYPE_1__ ntlm_unicode_ctx ;
typedef  int /*<<< orphan*/  ntlm_client ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 

ntlm_unicode_ctx *ntlm_unicode_ctx_init(ntlm_client *ntlm)
{
	ntlm_unicode_ctx *ctx;

	if ((ctx = malloc(sizeof(ntlm_unicode_ctx))) == NULL)
		return NULL;

	ctx->ntlm = ntlm;
	return ctx;
}
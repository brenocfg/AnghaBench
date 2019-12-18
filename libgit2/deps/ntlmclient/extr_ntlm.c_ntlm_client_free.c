#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  unicode_ctx; int /*<<< orphan*/  hmac_ctx; } ;
typedef  TYPE_1__ ntlm_client ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  ntlm_client_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  ntlm_hmac_ctx_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntlm_unicode_ctx_free (int /*<<< orphan*/ ) ; 

void ntlm_client_free(ntlm_client *ntlm)
{
	if (!ntlm)
		return;

	ntlm_client_reset(ntlm);

	ntlm_hmac_ctx_free(ntlm->hmac_ctx);
	ntlm_unicode_ctx_free(ntlm->unicode_ctx);

	free(ntlm);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ntlm_client_flags ;
struct TYPE_7__ {int /*<<< orphan*/ * unicode_ctx; int /*<<< orphan*/ * hmac_ctx; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ ntlm_client ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntlm_hmac_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ntlm_hmac_ctx_init () ; 
 int /*<<< orphan*/  ntlm_unicode_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ntlm_unicode_ctx_init (TYPE_1__*) ; 

ntlm_client *ntlm_client_init(ntlm_client_flags flags)
{
	ntlm_client *ntlm = NULL;

	if ((ntlm = malloc(sizeof(ntlm_client))) == NULL)
		return NULL;

	memset(ntlm, 0, sizeof(ntlm_client));

	ntlm->flags = flags;

	if ((ntlm->hmac_ctx = ntlm_hmac_ctx_init()) == NULL ||
		(ntlm->unicode_ctx = ntlm_unicode_ctx_init(ntlm)) == NULL) {
		ntlm_hmac_ctx_free(ntlm->hmac_ctx);
		ntlm_unicode_ctx_free(ntlm->unicode_ctx);
		free(ntlm);
		return NULL;
	}

	return ntlm;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * target; int /*<<< orphan*/  unicode_ctx; int /*<<< orphan*/  target_utf16_len; int /*<<< orphan*/ * target_utf16; } ;
typedef  TYPE_1__ ntlm_client ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntlm_client_set_errmsg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ntlm_unicode_utf8_to_16 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ supports_unicode (TYPE_1__*) ; 

int ntlm_client_set_target(ntlm_client *ntlm, const char *target)
{
	assert(ntlm);

	free(ntlm->target);
	free(ntlm->target_utf16);

	ntlm->target = NULL;
	ntlm->target_utf16 = NULL;

	if (target) {
		if ((ntlm->target = strdup(target)) == NULL) {
			ntlm_client_set_errmsg(ntlm, "out of memory");
			return -1;
		}

		if (supports_unicode(ntlm) && !ntlm_unicode_utf8_to_16(
				&ntlm->target_utf16,
				&ntlm->target_utf16_len,
				ntlm->unicode_ctx,
				ntlm->target,
				strlen(ntlm->target)))
			return -1;
	}

	return 0;
}
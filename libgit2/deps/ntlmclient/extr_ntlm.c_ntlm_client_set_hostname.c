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
struct TYPE_6__ {int /*<<< orphan*/  unicode_ctx; int /*<<< orphan*/  hostname_utf16_len; int /*<<< orphan*/ * hostname_utf16; int /*<<< orphan*/ * hostdomain; int /*<<< orphan*/ * hostname; } ;
typedef  TYPE_1__ ntlm_client ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntlm_client_set_errmsg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ntlm_unicode_utf8_to_16 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ supports_unicode (TYPE_1__*) ; 

int ntlm_client_set_hostname(
	ntlm_client *ntlm,
	const char *hostname,
	const char *domain)
{
	assert(ntlm);

	free(ntlm->hostname);
	free(ntlm->hostdomain);
	free(ntlm->hostname_utf16);

	ntlm->hostname = NULL;
	ntlm->hostdomain = NULL;
	ntlm->hostname_utf16 = NULL;

	if (hostname && (ntlm->hostname = strdup(hostname)) == NULL) {
		ntlm_client_set_errmsg(ntlm, "out of memory");
		return -1;
	}

	if (domain && (ntlm->hostdomain = strdup(domain)) == NULL) {
		ntlm_client_set_errmsg(ntlm, "out of memory");
		return -1;
	}

	if (hostname && supports_unicode(ntlm) && !ntlm_unicode_utf8_to_16(
			&ntlm->hostname_utf16,
			&ntlm->hostname_utf16_len,
			ntlm->unicode_ctx,
			hostname,
			strlen(hostname)))
		return -1;

	return 0;
}
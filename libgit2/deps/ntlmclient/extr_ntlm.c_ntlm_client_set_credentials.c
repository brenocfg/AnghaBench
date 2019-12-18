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
struct TYPE_7__ {int /*<<< orphan*/ * userdomain; int /*<<< orphan*/  unicode_ctx; int /*<<< orphan*/  userdomain_utf16_len; int /*<<< orphan*/  userdomain_utf16; int /*<<< orphan*/ * username_upper; int /*<<< orphan*/  username_upper_utf16_len; int /*<<< orphan*/  username_upper_utf16; int /*<<< orphan*/ * username; int /*<<< orphan*/  username_utf16_len; int /*<<< orphan*/  username_utf16; int /*<<< orphan*/ * password; } ;
typedef  TYPE_1__ ntlm_client ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  free_credentials (TYPE_1__*) ; 
 int /*<<< orphan*/  ntlm_client_set_errmsg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ntlm_unicode_utf8_to_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ supports_unicode (TYPE_1__*) ; 
 int /*<<< orphan*/  utf8upr (int /*<<< orphan*/ *) ; 

int ntlm_client_set_credentials(
	ntlm_client *ntlm,
	const char *username,
	const char *domain,
	const char *password)
{
	assert(ntlm);

	free_credentials(ntlm);

	if ((username && (ntlm->username = strdup(username)) == NULL) ||
		(domain && (ntlm->userdomain = strdup(domain)) == NULL) ||
		(password && (ntlm->password = strdup(password)) == NULL)) {
		ntlm_client_set_errmsg(ntlm, "out of memory");
		return -1;
	}

	if (username && supports_unicode(ntlm)) {
		if ((ntlm->username_upper = strdup(username)) == NULL) {
			ntlm_client_set_errmsg(ntlm, "out of memory");
			return -1;
		}
		utf8upr(ntlm->username_upper);

		if (!ntlm_unicode_utf8_to_16(
				&ntlm->username_utf16,
				&ntlm->username_utf16_len,
				ntlm->unicode_ctx,
				ntlm->username,
				strlen(ntlm->username)))
			return -1;

		if (!ntlm_unicode_utf8_to_16(
				&ntlm->username_upper_utf16,
				&ntlm->username_upper_utf16_len,
				ntlm->unicode_ctx,
				ntlm->username_upper,
				strlen(ntlm->username_upper)))
			return -1;
	}

	if (domain && supports_unicode(ntlm) && !ntlm_unicode_utf8_to_16(
			&ntlm->userdomain_utf16,
			&ntlm->userdomain_utf16_len,
			ntlm->unicode_ctx,
			ntlm->userdomain,
			strlen(ntlm->userdomain)))
		return -1;

	return 0;
}
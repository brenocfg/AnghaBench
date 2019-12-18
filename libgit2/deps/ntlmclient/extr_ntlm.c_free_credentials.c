#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * password_utf16; int /*<<< orphan*/ * userdomain_utf16; int /*<<< orphan*/ * username_upper_utf16; int /*<<< orphan*/ * username_utf16; int /*<<< orphan*/ * password; int /*<<< orphan*/ * userdomain; int /*<<< orphan*/ * username_upper; int /*<<< orphan*/ * username; int /*<<< orphan*/  password_utf16_len; } ;
typedef  TYPE_1__ ntlm_client ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_credentials(ntlm_client *ntlm)
{
	if (ntlm->password)
		memzero(ntlm->password, strlen(ntlm->password));

	if (ntlm->password_utf16)
		memzero(ntlm->password_utf16, ntlm->password_utf16_len);

	free(ntlm->username);
	free(ntlm->username_upper);
	free(ntlm->userdomain);
	free(ntlm->password);

	free(ntlm->username_utf16);
	free(ntlm->username_upper_utf16);
	free(ntlm->userdomain_utf16);
	free(ntlm->password_utf16);

	ntlm->username = NULL;
	ntlm->username_upper = NULL;
	ntlm->userdomain = NULL;
	ntlm->password = NULL;

	ntlm->username_utf16 = NULL;
	ntlm->username_upper_utf16 = NULL;
	ntlm->userdomain_utf16 = NULL;
	ntlm->password_utf16 = NULL;
}
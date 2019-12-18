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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {int CredentialBlobSize; scalar_t__ CredentialBlob; scalar_t__ UserName; } ;
typedef  scalar_t__ LPCWSTR ;
typedef  int DWORD ;
typedef  TYPE_1__ CREDENTIALW ;

/* Variables and functions */
 int /*<<< orphan*/  CredEnumerateW (char*,int /*<<< orphan*/ ,int*,TYPE_1__***) ; 
 int /*<<< orphan*/  CredFree (TYPE_1__**) ; 
 scalar_t__ match_cred (TYPE_1__*) ; 
 int wcslen (scalar_t__) ; 
 int /*<<< orphan*/  write_item (char*,scalar_t__,int) ; 

__attribute__((used)) static void get_credential(void)
{
	CREDENTIALW **creds;
	DWORD num_creds;
	int i;

	if (!CredEnumerateW(L"git:*", 0, &num_creds, &creds))
		return;

	/* search for the first credential that matches username */
	for (i = 0; i < num_creds; ++i)
		if (match_cred(creds[i])) {
			write_item("username", creds[i]->UserName,
				creds[i]->UserName ? wcslen(creds[i]->UserName) : 0);
			write_item("password",
				(LPCWSTR)creds[i]->CredentialBlob,
				creds[i]->CredentialBlobSize / sizeof(WCHAR));
			break;
		}

	CredFree(creds);
}
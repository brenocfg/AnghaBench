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
struct TYPE_5__ {int /*<<< orphan*/  Type; int /*<<< orphan*/  TargetName; } ;
typedef  int DWORD ;
typedef  TYPE_1__ CREDENTIALW ;

/* Variables and functions */
 int /*<<< orphan*/  CredDeleteW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CredEnumerateW (char*,int /*<<< orphan*/ ,int*,TYPE_1__***) ; 
 int /*<<< orphan*/  CredFree (TYPE_1__**) ; 
 scalar_t__ match_cred (TYPE_1__*) ; 

__attribute__((used)) static void erase_credential(void)
{
	CREDENTIALW **creds;
	DWORD num_creds;
	int i;

	if (!CredEnumerateW(L"git:*", 0, &num_creds, &creds))
		return;

	for (i = 0; i < num_creds; ++i) {
		if (match_cred(creds[i]))
			CredDeleteW(creds[i]->TargetName, creds[i]->Type, 0);
	}

	CredFree(creds);
}
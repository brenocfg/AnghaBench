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
struct TYPE_3__ {char* UserName; int /*<<< orphan*/  TargetName; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_1__ CREDENTIALW ;

/* Variables and functions */
 char* host ; 
 scalar_t__ match_part (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ match_part_last (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 char* path ; 
 char* protocol ; 
 scalar_t__ wcscmp (scalar_t__,char*) ; 
 scalar_t__ wusername ; 

__attribute__((used)) static int match_cred(const CREDENTIALW *cred)
{
	LPCWSTR target = cred->TargetName;
	if (wusername && wcscmp(wusername, cred->UserName ? cred->UserName : L""))
		return 0;

	return match_part(&target, L"git", L":") &&
		match_part(&target, protocol, L"://") &&
		match_part_last(&target, wusername, L"@") &&
		match_part(&target, host, L"/") &&
		match_part(&target, path, L"");
}
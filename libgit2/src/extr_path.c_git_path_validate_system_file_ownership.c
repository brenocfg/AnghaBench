#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_win32_path ;
struct TYPE_8__ {int /*<<< orphan*/  Sid; } ;
struct TYPE_9__ {TYPE_1__ User; } ;
typedef  TYPE_2__ TOKEN_USER ;
typedef  int /*<<< orphan*/  PSID ;
typedef  int /*<<< orphan*/ * PSECURITY_DESCRIPTOR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int DACL_SECURITY_INFORMATION ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_PATH_NOT_FOUND ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ EqualSid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GIT_ENOTFOUND ; 
 int GIT_ERROR ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int GIT_OK ; 
 int /*<<< orphan*/  GIT_UNUSED (char const*) ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 scalar_t__ GetNamedSecurityInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GetTokenInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  IsValidSid (int /*<<< orphan*/ ) ; 
 scalar_t__ IsWellKnownSid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int OWNER_SECURITY_INFORMATION ; 
 scalar_t__ OpenProcessToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SE_FILE_OBJECT ; 
 int /*<<< orphan*/  TOKEN_QUERY ; 
 int /*<<< orphan*/  TokenUser ; 
 int /*<<< orphan*/  WinBuiltinAdministratorsSid ; 
 int /*<<< orphan*/  WinLocalSystemSid ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  git__free (TYPE_2__*) ; 
 TYPE_2__* git__malloc (scalar_t__) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_win32_path_from_utf8 (int /*<<< orphan*/ ,char const*) ; 

int git_path_validate_system_file_ownership(const char *path)
{
#ifndef GIT_WIN32
	GIT_UNUSED(path);
	return GIT_OK;
#else
	git_win32_path buf;
	PSID owner_sid;
	PSECURITY_DESCRIPTOR descriptor = NULL;
	HANDLE token;
	TOKEN_USER *info = NULL;
	DWORD err, len;
	int ret;

	if (git_win32_path_from_utf8(buf, path) < 0)
		return -1;

	err = GetNamedSecurityInfoW(buf, SE_FILE_OBJECT,
				    OWNER_SECURITY_INFORMATION |
					    DACL_SECURITY_INFORMATION,
				    &owner_sid, NULL, NULL, NULL, &descriptor);

	if (err == ERROR_FILE_NOT_FOUND || err == ERROR_PATH_NOT_FOUND) {
		ret = GIT_ENOTFOUND;
		goto cleanup;
	}

	if (err != ERROR_SUCCESS) {
		git_error_set(GIT_ERROR_OS, "failed to get security information");
		ret = GIT_ERROR;
		goto cleanup;
	}

	if (!IsValidSid(owner_sid)) {
		git_error_set(GIT_ERROR_INVALID, "programdata configuration file owner is unknown");
		ret = GIT_ERROR;
		goto cleanup;
	}

	if (IsWellKnownSid(owner_sid, WinBuiltinAdministratorsSid) ||
	    IsWellKnownSid(owner_sid, WinLocalSystemSid)) {
		ret = GIT_OK;
		goto cleanup;
	}

	/* Obtain current user's SID */
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token) &&
	    !GetTokenInformation(token, TokenUser, NULL, 0, &len)) {
		info = git__malloc(len);
		GIT_ERROR_CHECK_ALLOC(info);
		if (!GetTokenInformation(token, TokenUser, info, len, &len)) {
			git__free(info);
			info = NULL;
		}
	}

	/*
	 * If the file is owned by the same account that is running the current
	 * process, it's okay to read from that file.
	 */
	if (info && EqualSid(owner_sid, info->User.Sid))
		ret = GIT_OK;
	else {
		git_error_set(GIT_ERROR_INVALID, "programdata configuration file owner is not valid");
		ret = GIT_ERROR;
	}
	free(info);

cleanup:
	if (descriptor)
		LocalFree(descriptor);

	return ret;
#endif
}
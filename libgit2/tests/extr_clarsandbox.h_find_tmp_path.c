#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ GetEnvironmentVariable (char*,char*,scalar_t__) ; 
 scalar_t__ GetTempPath (scalar_t__,char*) ; 
 size_t PATH_MAX ; 
 char* getenv (char const*) ; 
 scalar_t__ is_valid_tmp_path (char const*) ; 
 int /*<<< orphan*/ * realpath (char const*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static int
find_tmp_path(char *buffer, size_t length)
{
#ifndef _WIN32
	static const size_t var_count = 5;
	static const char *env_vars[] = {
		"CLAR_TMP", "TMPDIR", "TMP", "TEMP", "USERPROFILE"
 	};

 	size_t i;

	for (i = 0; i < var_count; ++i) {
		const char *env = getenv(env_vars[i]);
		if (!env)
			continue;

		if (is_valid_tmp_path(env)) {
#ifdef __APPLE__
			if (length >= PATH_MAX && realpath(env, buffer) != NULL)
				return 0;
#endif
			strncpy(buffer, env, length);
			return 0;
		}
	}

	/* If the environment doesn't say anything, try to use /tmp */
	if (is_valid_tmp_path("/tmp")) {
#ifdef __APPLE__
		if (length >= PATH_MAX && realpath("/tmp", buffer) != NULL)
			return 0;
#endif
		strncpy(buffer, "/tmp", length);
		return 0;
	}

#else
	DWORD env_len = GetEnvironmentVariable("CLAR_TMP", buffer, (DWORD)length);
	if (env_len > 0 && env_len < (DWORD)length)
		return 0;

	if (GetTempPath((DWORD)length, buffer))
		return 0;
#endif

	/* This system doesn't like us, try to use the current directory */
	if (is_valid_tmp_path(".")) {
		strncpy(buffer, ".", length);
		return 0;
	}

	return -1;
}
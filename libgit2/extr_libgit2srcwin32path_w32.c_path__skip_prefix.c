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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  PATH__ABSOLUTE_LEN ; 
 int /*<<< orphan*/  PATH__NT_NAMESPACE_LEN ; 
 scalar_t__ git_path_is_absolute (int /*<<< orphan*/ *) ; 
 scalar_t__ path__is_nt_namespace (int /*<<< orphan*/ *) ; 
 scalar_t__ path__is_unc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * path__skip_server (int /*<<< orphan*/ *) ; 
 scalar_t__ wcsncmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static wchar_t *path__skip_prefix(wchar_t *path)
{
	if (path__is_nt_namespace(path)) {
		path += PATH__NT_NAMESPACE_LEN;

		if (wcsncmp(path, L"UNC\\", 4) == 0)
			path = path__skip_server(path + 4);
		else if (git_path_is_absolute(path))
			path += PATH__ABSOLUTE_LEN;
	} else if (git_path_is_absolute(path)) {
		path += PATH__ABSOLUTE_LEN;
	} else if (path__is_unc(path)) {
		path = path__skip_server(path + 2);
	}

	return path;
}
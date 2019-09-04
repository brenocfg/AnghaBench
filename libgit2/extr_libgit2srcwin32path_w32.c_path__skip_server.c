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
typedef  scalar_t__ wchar_t ;

/* Variables and functions */
 scalar_t__ git_path_is_dirsep (scalar_t__) ; 

__attribute__((used)) static wchar_t *path__skip_server(wchar_t *path)
{
	wchar_t *c;

	for (c = path; *c; c++) {
		if (git_path_is_dirsep(*c))
			return c + 1;
	}

	return c;
}
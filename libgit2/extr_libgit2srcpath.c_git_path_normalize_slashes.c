#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int git_buf_puts (TYPE_1__*,char const*) ; 

int git_path_normalize_slashes(git_buf *out, const char *path)
{
	int error;
	char *p;

	if ((error = git_buf_puts(out, path)) < 0)
		return error;

	for (p = out->ptr; *p; p++) {
		if (*p == '\\')
			*p = '/';
	}

	return 0;
}
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

/* Variables and functions */
 scalar_t__ __libc_restricted_mode ; 
 int /*<<< orphan*/  _rtld_error (char*) ; 
 void* dlopen (char const*,int) ; 

void *
libc_dlopen(const char *path, int mode)
{

	if (__libc_restricted_mode) {
		_rtld_error("Service unavailable -- libc in restricted mode");
		return (NULL);
	}
	return (dlopen(path, mode));
}
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
 scalar_t__ exitnow ; 
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  fout ; 
 scalar_t__ mtflag ; 
 scalar_t__ timerflag ; 

__attribute__((used)) static void
print_return(const char *space)
{
	if (exitnow)
		f_print(fout, "%sexit(0);\n", space);
	else {
		if (timerflag) {
			if (mtflag)
				f_print(fout, "%spthread_mutex_lock(&_svcstate_lock);\n", space);
				f_print(fout, "%s_rpcsvcstate = _SERVED;\n", space);
			if (mtflag)
				f_print(fout, "%spthread_mutex_unlock(&_svcstate_lock);\n", space);
		}
		f_print(fout, "%sreturn;\n", space);
	}
}
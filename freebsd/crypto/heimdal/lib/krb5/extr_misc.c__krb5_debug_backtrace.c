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
typedef  int /*<<< orphan*/  stack ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  _krb5_debug (int /*<<< orphan*/ ,int,char*,int,char*) ; 
 int backtrace (void**,int) ; 
 char** backtrace_symbols (void**,int) ; 
 int /*<<< orphan*/  free (char**) ; 

void
_krb5_debug_backtrace(krb5_context context)
{
#if defined(HAVE_BACKTRACE) && !defined(HEIMDAL_SMALLER)
    void *stack[128];
    char **strs = NULL;
    int i, frames = backtrace(stack, sizeof(stack) / sizeof(stack[0]));
    if (frames > 0)
	strs = backtrace_symbols(stack, frames);
    if (strs) {
	for (i = 0; i < frames; i++)
	    _krb5_debug(context, 10, "frame %d: %s", i, strs[i]);
	free(strs);
    }
#endif
}
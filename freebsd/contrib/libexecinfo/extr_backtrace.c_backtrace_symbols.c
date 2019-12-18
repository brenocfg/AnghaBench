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
 char** backtrace_symbols_fmt (void* const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmt ; 

char **
backtrace_symbols(void *const *trace, size_t len)
{
	return backtrace_symbols_fmt(trace, len, fmt);
}
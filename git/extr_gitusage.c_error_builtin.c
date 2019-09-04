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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  trace2_cmd_error_va (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vreportf (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void error_builtin(const char *err, va_list params)
{
	/*
	 * We call this trace2 function first and expect it to va_copy 'params'
	 * before using it (because an 'ap' can only be walked once).
	 */
	trace2_cmd_error_va(err, params);

	vreportf("error: ", err, params);
}
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
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_trace_dump_funcname (char*,int (*) ()) ; 
 int /*<<< orphan*/  wpa_trace_show (char*) ; 

__attribute__((used)) static int trace_tests(void)
{
	wpa_printf(MSG_INFO, "trace tests");

	wpa_trace_show("test backtrace");
	wpa_trace_dump_funcname("test funcname", trace_tests);

	return 0;
}
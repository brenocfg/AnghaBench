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
 int /*<<< orphan*/  G_BREAKPOINT () ; 
 int /*<<< orphan*/  g_critical (char*,char*,char*) ; 
 char* g_strdup_printf (char*,char const*,char const*,char const*,char const*) ; 
 char* g_strdup_vprintf (char const*,int /*<<< orphan*/ ) ; 

void uiprivRealBug(const char *file, const char *line, const char *func, const char *prefix, const char *format, va_list ap)
{
	char *a, *b;

	a = g_strdup_printf("[libui] %s:%s:%s() %s", file, line, func, prefix);
	b = g_strdup_vprintf(format, ap);
	g_critical("%s%s", a, b);
	G_BREAKPOINT();
}
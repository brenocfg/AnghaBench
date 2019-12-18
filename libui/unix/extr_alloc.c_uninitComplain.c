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
typedef  scalar_t__ gpointer ;

/* Variables and functions */
 int /*<<< orphan*/ * TYPE (scalar_t__) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup_printf (char*,...) ; 

__attribute__((used)) static void uninitComplain(gpointer ptr, gpointer data)
{
	char **str = (char **) data;
	char *str2;

	if (*str == NULL)
		*str = g_strdup_printf("");
	str2 = g_strdup_printf("%s%p %s\n", *str, ptr, *TYPE(ptr));
	g_free(*str);
	*str = str2;
}
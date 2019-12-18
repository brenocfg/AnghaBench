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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ocs_textbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_textbuf_printf (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 

void
ocs_ddump_section(ocs_textbuf_t *textbuf, const char *name, uint32_t instance)
{
	ocs_textbuf_printf(textbuf, "<%s type=\"section\" instance=\"%d\">\n", name, instance);
}
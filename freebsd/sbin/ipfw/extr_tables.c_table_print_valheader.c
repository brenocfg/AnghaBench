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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ IPFW_VTYPE_LEGACY ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  print_flags_buffer (char*,size_t,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*) ; 
 int /*<<< orphan*/  tablevaltypes ; 

__attribute__((used)) static void
table_print_valheader(char *buf, size_t bufsize, uint32_t vmask)
{

	if (vmask == IPFW_VTYPE_LEGACY) {
		snprintf(buf, bufsize, "legacy");
		return;
	}

	memset(buf, 0, bufsize);
	print_flags_buffer(buf, bufsize, tablevaltypes, vmask);
}
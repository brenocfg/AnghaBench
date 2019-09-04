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
 int /*<<< orphan*/  server_capabilities_v1 ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static void process_capabilities(const char *line, int *len)
{
	int nul_location = strlen(line);
	if (nul_location == *len)
		return;
	server_capabilities_v1 = xstrdup(line + nul_location + 1);
	*len = nul_location;
}
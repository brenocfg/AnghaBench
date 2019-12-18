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
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strspn (char const*,char*) ; 

__attribute__((used)) static int
is_addr_fast(const char *name)
{
	return (strchr(name, '%') != NULL || strchr(name, ':') != NULL ||
	    strspn(name, "0123456789.") == strlen(name));
}
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
 scalar_t__ ns_samedomain (char const*,char const*) ; 
 int ns_samename (char const*,char const*) ; 

int
ns_subdomain(const char *a, const char *b) {
	return (ns_samename(a, b) != 1 && ns_samedomain(a, b));
}
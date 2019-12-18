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
typedef  scalar_t__ u_int16_t ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/ * hook_p ;

/* Variables and functions */
 int /*<<< orphan*/ * ng_ipfw_findhook1 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strtol (char const*,char**,int) ; 

__attribute__((used)) static hook_p
ng_ipfw_findhook(node_p node, const char *name)
{
	u_int16_t n;	/* numeric representation of hook */
	char *endptr;

	n = (u_int16_t)strtol(name, &endptr, 10);
	if (*endptr != '\0')
		return NULL;
	return ng_ipfw_findhook1(node, n);
}
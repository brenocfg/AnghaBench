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
typedef  int /*<<< orphan*/  u_quad_t ;

/* Variables and functions */
 int /*<<< orphan*/  strtoull (char const*,char**,int) ; 

u_quad_t
strtouq(const char *nptr, char **endptr, int base)
{

	return strtoull(nptr, endptr, base);
}
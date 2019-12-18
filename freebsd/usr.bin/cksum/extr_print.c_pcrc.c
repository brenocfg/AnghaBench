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
typedef  int /*<<< orphan*/  u_long ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void
pcrc(char *fn, uint32_t val, off_t len)
{
	(void)printf("%lu %jd", (u_long)val, (intmax_t)len);
	if (fn != NULL)
		(void)printf(" %s", fn);
	(void)printf("\n");
}
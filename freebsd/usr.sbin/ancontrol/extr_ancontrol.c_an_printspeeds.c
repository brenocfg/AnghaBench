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
typedef  double u_int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
an_printspeeds(const u_int8_t *w, int len)
{
	int			i;

	printf("[ ");
	for (i = 0; i < len && w[i]; i++)
		printf("%2.1fMbps ", w[i] * 0.500);
	printf("]");
}
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
 int EOF ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int getchar () ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
pkg_query_yes_no(void)
{
	int ret, c;

	fflush(stdout);
	c = getchar();

	if (c == 'y' || c == 'Y')
		ret = 1;
	else
		ret = 0;

	while (c != '\n' && c != EOF)
		c = getchar();

	return (ret);
}
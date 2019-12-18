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
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
checkitemsize(
	size_t itemsize,
	size_t expected
	)
{
	if (itemsize != expected) {
		(void) fprintf(stderr,
			       "***Incorrect item size returned by remote host (%lu should be %lu)\n",
			       (u_long)itemsize, (u_long)expected);
		return 0;
	}
	return 1;
}
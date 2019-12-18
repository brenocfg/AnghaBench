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
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 scalar_t__ pipe (int*) ; 

__attribute__((used)) static void
setup_pipe(const char *test, int *fdp)
{

	if (pipe(fdp) < 0)
		err(1, "%s: setup_pipe: pipe", test);
}
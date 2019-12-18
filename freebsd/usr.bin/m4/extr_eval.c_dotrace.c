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
 int /*<<< orphan*/  mark_traced (char const*,int) ; 

__attribute__((used)) static void
dotrace(const char *argv[], int argc, int on)
{
	int n;

	if (argc > 2) {
		for (n = 2; n < argc; n++)
			mark_traced(argv[n], on);
	} else
		mark_traced(NULL, on);
}
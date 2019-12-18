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
 scalar_t__ EOF ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ putchar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 long strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int cmd__genzeros(int argc, const char **argv)
{
	long count;

	if (argc > 2) {
		fprintf(stderr, "usage: %s [<count>]\n", argv[0]);
		return 1;
	}

	count = argc > 1 ? strtol(argv[1], NULL, 0) : -1L;

	while (count < 0 || count--) {
		if (putchar(0) == EOF)
			return -1;
	}

	return 0;
}
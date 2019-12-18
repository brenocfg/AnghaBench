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
 scalar_t__ putchar (unsigned long) ; 
 int /*<<< orphan*/  stderr ; 
 long strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int cmd__genrandom(int argc, const char **argv)
{
	unsigned long count, next = 0;
	unsigned char *c;

	if (argc < 2 || argc > 3) {
		fprintf(stderr, "usage: %s <seed_string> [<size>]\n", argv[0]);
		return 1;
	}

	c = (unsigned char *) argv[1];
	do {
		next = next * 11 + *c;
	} while (*c++);

	count = (argc == 3) ? strtoul(argv[2], NULL, 0) : -1L;

	while (count--) {
		next = next * 1103515245 + 12345;
		if (putchar((next >> 16) & 0xff) == EOF)
			return -1;
	}

	return 0;
}
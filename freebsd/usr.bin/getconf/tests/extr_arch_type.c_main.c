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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 

int
main(void)
{
	bool known_arch_type;

	known_arch_type = false;
#ifdef	__LP64__
	printf("LP64\n");
	known_arch_type = true;
#endif
#ifdef	__LP32__
	printf("LP32\n");
	known_arch_type = true;
#endif
#ifdef	__ILP32__
	printf("ILP32\n");
	known_arch_type = true;
#endif

	if (known_arch_type)
		exit(0);

	fprintf(stderr, "unknown architecture type detected\n");
	assert(0);
}
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
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 scalar_t__ mincore (void*,size_t,char*) ; 
 size_t page ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static size_t
check_residency(void *addr, size_t npgs)
{
	size_t i, resident;
	char *vec;

	vec = malloc(npgs);

	ATF_REQUIRE(vec != NULL);
	ATF_REQUIRE(mincore(addr, npgs * page, vec) == 0);

	for (i = resident = 0; i < npgs; i++) {

		if (vec[i] != 0)
			resident++;

#if 0
		(void)fprintf(stderr, "page 0x%p is %sresident\n",
		    (char *)addr + (i * page), vec[i] ? "" : "not ");
#endif
	}

	free(vec);

	return resident;
}
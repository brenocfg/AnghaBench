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
struct scgs_vector {size_t offset; size_t size; int /*<<< orphan*/ * sysctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ *,size_t,size_t) ; 
 int sysctlbyname (int /*<<< orphan*/ *,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
sysctlgatherstruct(void *addr, size_t size, struct scgs_vector *vecarr)
{
	struct scgs_vector *xp;
	size_t tsiz;
	int rv;

	for (xp = vecarr; xp->sysctl != NULL; xp++) {
		assert(xp->offset <= size);
		tsiz = xp->size;
		rv = sysctlbyname(xp->sysctl, (char *)addr + xp->offset,
		    &tsiz, NULL, 0);
		if (rv == -1)
			err(1, "sysctlbyname: %s", xp->sysctl);
		if (tsiz != xp->size)
			errx(1, "%s size mismatch (expected %zu, got %zu)",
			    xp->sysctl, xp->size, tsiz);
	}
}
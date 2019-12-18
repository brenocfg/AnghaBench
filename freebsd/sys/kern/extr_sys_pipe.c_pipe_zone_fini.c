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
struct pipepair {int /*<<< orphan*/  pp_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pipe_zone_fini(void *mem, int size)
{
	struct pipepair *pp;

	KASSERT(size == sizeof(*pp), ("pipe_zone_fini: wrong size"));

	pp = (struct pipepair *)mem;

	mtx_destroy(&pp->pp_mtx);
}
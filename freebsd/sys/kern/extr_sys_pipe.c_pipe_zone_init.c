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
 int MTX_DEF ; 
 int MTX_NEW ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
pipe_zone_init(void *mem, int size, int flags)
{
	struct pipepair *pp;

	KASSERT(size == sizeof(*pp), ("pipe_zone_init: wrong size"));

	pp = (struct pipepair *)mem;

	mtx_init(&pp->pp_mtx, "pipe mutex", NULL, MTX_DEF | MTX_NEW);
	return (0);
}
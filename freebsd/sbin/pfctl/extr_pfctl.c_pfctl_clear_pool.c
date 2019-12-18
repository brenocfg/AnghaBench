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
struct pf_pooladdr {int dummy; } ;
struct pf_pool {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 struct pf_pooladdr* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pf_pooladdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  free (struct pf_pooladdr*) ; 

void
pfctl_clear_pool(struct pf_pool *pool)
{
	struct pf_pooladdr *pa;

	while ((pa = TAILQ_FIRST(&pool->list)) != NULL) {
		TAILQ_REMOVE(&pool->list, pa, entries);
		free(pa);
	}
}
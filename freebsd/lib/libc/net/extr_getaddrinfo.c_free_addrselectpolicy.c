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
struct policyqueue {int dummy; } ;
struct policyhead {int dummy; } ;

/* Variables and functions */
 struct policyqueue* TAILQ_FIRST (struct policyhead*) ; 
 struct policyqueue* TAILQ_NEXT (struct policyqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct policyhead*,struct policyqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct policyqueue*) ; 
 int /*<<< orphan*/  pc_entry ; 

__attribute__((used)) static void
free_addrselectpolicy(struct policyhead *head)
{
	struct policyqueue *ent, *nent;

	for (ent = TAILQ_FIRST(head); ent; ent = nent) {
		nent = TAILQ_NEXT(ent, pc_entry);
		TAILQ_REMOVE(head, ent, pc_entry);
		free(ent);
	}
}
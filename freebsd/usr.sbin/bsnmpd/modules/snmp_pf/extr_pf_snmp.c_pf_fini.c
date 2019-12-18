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
struct pft_entry {int dummy; } ;
typedef  struct pft_entry pfq_entry ;
typedef  struct pft_entry pfl_entry ;
typedef  struct pft_entry pfi_entry ;
typedef  struct pft_entry pfa_entry ;

/* Variables and functions */
 struct pft_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct pft_entry* TAILQ_NEXT (struct pft_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  free (struct pft_entry*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  pfa_table ; 
 int /*<<< orphan*/  pfi_table ; 
 int /*<<< orphan*/  pfl_table ; 
 int /*<<< orphan*/  pfq_table ; 
 int /*<<< orphan*/  pft_table ; 

__attribute__((used)) static int
pf_fini(void)
{
	struct pfi_entry *i1, *i2;
	struct pfq_entry *q1, *q2;
	struct pft_entry *t1, *t2;
	struct pfa_entry *a1, *a2;
	struct pfl_entry *l1, *l2;

	/* Empty the list of interfaces */
	i1 = TAILQ_FIRST(&pfi_table);
	while (i1 != NULL) {
		i2 = TAILQ_NEXT(i1, link);
		free(i1);
		i1 = i2;
	}

	/* List of queues */
	q1 = TAILQ_FIRST(&pfq_table);
	while (q1 != NULL) {
		q2 = TAILQ_NEXT(q1, link);
		free(q1);
		q1 = q2;
	}

	/* List of tables */
	t1 = TAILQ_FIRST(&pft_table);
	while (t1 != NULL) {
		t2 = TAILQ_NEXT(t1, link);
		free(t1);
		t1 = t2;
	}

	/* List of table addresses */
	a1 = TAILQ_FIRST(&pfa_table);
	while (a1 != NULL) {
		a2 = TAILQ_NEXT(a1, link);
		free(a1);
		a1 = a2;
	}

	/* And the list of labeled filter rules */
	l1 = TAILQ_FIRST(&pfl_table);
	while (l1 != NULL) {
		l2 = TAILQ_NEXT(l1, link);
		free(l1);
		l1 = l2;
	}

	close(dev);
	return (0);
}
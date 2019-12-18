#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  n_name; } ;
struct TYPE_7__ {scalar_t__ n_refcnt; int n_flags; struct TYPE_7__* n_next; } ;
typedef  TYPE_1__ NODE ;

/* Variables and functions */
 int NF_ACYCLIC ; 
 int /*<<< orphan*/  clear_cycle () ; 
 int /*<<< orphan*/ * cycle_buf ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int find_cycle (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* graph ; 
 TYPE_3__** longest_cycle ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  quiet ; 
 int /*<<< orphan*/  remove_node (TYPE_1__*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void
tsort(void)
{
	NODE *n, *next;
	int cnt, i;

	while (graph != NULL) {
		/*
		 * Keep getting rid of simple cases until there are none left,
		 * if there are any nodes still in the graph, then there is
		 * a cycle in it.
		 */
		do {
			for (cnt = 0, n = graph; n != NULL; n = next) {
				next = n->n_next;
				if (n->n_refcnt == 0) {
					remove_node(n);
					++cnt;
				}
			}
		} while (graph != NULL && cnt);

		if (graph == NULL)
			break;

		if (!cycle_buf) {
			/*
			 * Allocate space for two cycle logs - one to be used
			 * as scratch space, the other to save the longest
			 * cycle.
			 */
			for (cnt = 0, n = graph; n != NULL; n = n->n_next)
				++cnt;
			cycle_buf = malloc(sizeof(NODE *) * cnt);
			longest_cycle = malloc(sizeof(NODE *) * cnt);
			if (cycle_buf == NULL || longest_cycle == NULL)
				err(1, NULL);
		}
		for (n = graph; n != NULL; n = n->n_next)
			if (!(n->n_flags & NF_ACYCLIC)) {
				if ((cnt = find_cycle(n, n, 0, 0))) {
					if (!quiet) {
						warnx("cycle in data");
						for (i = 0; i < cnt; i++)
							warnx("%s",
							    longest_cycle[i]->n_name);
					}
					remove_node(n);
					clear_cycle();
					break;
				} else {
					/* to avoid further checks */
					n->n_flags  |= NF_ACYCLIC;
					clear_cycle();
				}
			}

		if (n == NULL)
			errx(1, "internal error -- could not find cycle");
	}
}
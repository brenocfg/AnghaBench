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
struct prio_queue {int /*<<< orphan*/ * compare; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  intcmp ; 
 void* prio_queue_get (struct prio_queue*) ; 
 void* prio_queue_peek (struct prio_queue*) ; 
 int /*<<< orphan*/  prio_queue_put (struct prio_queue*,int*) ; 
 int /*<<< orphan*/  show (void*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int* xmalloc (int) ; 

int cmd__prio_queue(int argc, const char **argv)
{
	struct prio_queue pq = { intcmp };

	while (*++argv) {
		if (!strcmp(*argv, "get")) {
			void *peek = prio_queue_peek(&pq);
			void *get = prio_queue_get(&pq);
			if (peek != get)
				BUG("peek and get results do not match");
			show(get);
		} else if (!strcmp(*argv, "dump")) {
			void *peek;
			void *get;
			while ((peek = prio_queue_peek(&pq))) {
				get = prio_queue_get(&pq);
				if (peek != get)
					BUG("peek and get results do not match");
				show(get);
			}
		} else if (!strcmp(*argv, "stack")) {
			pq.compare = NULL;
		} else {
			int *v = xmalloc(sizeof(*v));
			*v = atoi(*argv);
			prio_queue_put(&pq, v);
		}
	}

	return 0;
}
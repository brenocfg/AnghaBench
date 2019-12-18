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
typedef  int /*<<< orphan*/  uint64_t ;
struct list {struct list* next; } ;
struct gkc_tuple {double g; double delta; int /*<<< orphan*/  value; } ;
struct gkc_summary {double nr_elems; double epsilon; struct list head; } ;

/* Variables and functions */
 scalar_t__ list_empty (struct list*) ; 
 struct gkc_tuple* list_to_tuple (struct list*) ; 

uint64_t gkc_query(struct gkc_summary *s, double q)
{
    struct list *cur, *next;
    int rank;
    double gi;
    double ne;

    rank = 0.5 + q * s->nr_elems;
    ne = s->nr_elems * s->epsilon;
    gi = 0;
    if (list_empty(&s->head)) {
        return 0;
    }

    cur = s->head.next;

    while (1) {
        struct gkc_tuple *tcur, *tnext;

        tcur = list_to_tuple(cur);
        next = cur->next;
        if (next == &s->head) {
            return tcur->value;
        }
        tnext = list_to_tuple(next);

        gi += tcur->g;
        if ((rank + ne) < (gi + tnext->g + tnext->delta)) {
            if ((rank + ne) < (gi + tnext->g)) {
                return tcur->value;
            }
            return tnext->value;
        }
        cur = next;
    }
}
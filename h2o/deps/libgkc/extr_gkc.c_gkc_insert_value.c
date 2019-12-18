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
struct list {struct list* next; } ;
struct gkc_tuple {double value; int g; int delta; int /*<<< orphan*/  node; } ;
struct gkc_summary {int nr_elems; int epsilon; struct list head; } ;

/* Variables and functions */
 struct gkc_tuple* gkc_alloc (struct gkc_summary*) ; 
 int /*<<< orphan*/  gkc_compress (struct gkc_summary*) ; 
 int /*<<< orphan*/  list_add (struct list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (struct list*,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (struct list*) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 struct gkc_tuple* list_to_tuple (struct list*) ; 
 int /*<<< orphan*/  memset (struct gkc_tuple*,int /*<<< orphan*/ ,int) ; 

void gkc_insert_value(struct gkc_summary *s, double value)
{
    struct list *cur = NULL;
    struct gkc_tuple *new, *tcur, *tnext = NULL;

    new = gkc_alloc(s);
    memset(new, 0, sizeof(*new));
    new->value = value;
    new->g = 1;
    list_init(&new->node);


    s->nr_elems++;


    /* first insert */
    if (list_empty(&s->head)) {
        list_add(&s->head, &new->node);
        return;
    }

    cur = s->head.next;
    tcur = list_to_tuple(cur);
    /* v < v0, new min */
    if (tcur->value > new->value) {
        list_add(&s->head, &new->node);
        goto out;
    }

    double gi = 0;
    while (cur->next != &s->head) {
        tnext = list_to_tuple(cur->next);
        tcur = list_to_tuple(cur);

        gi += tcur->g;
        if (tcur->value <= new->value && new->value < tnext->value) {
            /*     INSERT "(v, 1, Δ)" into S between vi and vi+1; */
            new->delta = tcur->g + tcur->delta - 1;
            list_add(cur, &new->node);
            goto out;
        }
        cur = cur->next;
    }
    /* v > vs-1, new max */
    list_add_tail(&s->head, &new->node);
out:
    if (s->nr_elems % (int)(1/(2*s->epsilon))) {
        gkc_compress(s);
    }
}
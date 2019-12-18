#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; } ;
struct object {unsigned int flags; } ;
struct commit_list {struct commit_list* next; TYPE_1__* item; } ;
struct commit_dist {int distance; TYPE_1__* commit; } ;
struct TYPE_2__ {struct object object; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECORATION_NONE ; 
 int /*<<< orphan*/  QSORT (struct commit_dist*,int,int /*<<< orphan*/ ) ; 
 struct strbuf STRBUF_INIT ; 
 unsigned int TREESAME ; 
 int /*<<< orphan*/  add_name_decoration (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object*) ; 
 int /*<<< orphan*/  compare_commit_dist ; 
 int /*<<< orphan*/  free (struct commit_dist*) ; 
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int weight (struct commit_list*) ; 
 struct commit_dist* xcalloc (int,int) ; 

__attribute__((used)) static struct commit_list *best_bisection_sorted(struct commit_list *list, int nr)
{
	struct commit_list *p;
	struct commit_dist *array = xcalloc(nr, sizeof(*array));
	struct strbuf buf = STRBUF_INIT;
	int cnt, i;

	for (p = list, cnt = 0; p; p = p->next) {
		int distance;
		unsigned flags = p->item->object.flags;

		if (flags & TREESAME)
			continue;
		distance = weight(p);
		if (nr - distance < distance)
			distance = nr - distance;
		array[cnt].commit = p->item;
		array[cnt].distance = distance;
		cnt++;
	}
	QSORT(array, cnt, compare_commit_dist);
	for (p = list, i = 0; i < cnt; i++) {
		struct object *obj = &(array[i].commit->object);

		strbuf_reset(&buf);
		strbuf_addf(&buf, "dist=%d", array[i].distance);
		add_name_decoration(DECORATION_NONE, buf.buf, obj);

		p->item = array[i].commit;
		if (i < cnt - 1)
			p = p->next;
	}
	if (p) {
		free_commit_list(p->next);
		p->next = NULL;
	}
	strbuf_release(&buf);
	free(array);
	return list;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct diff_queue_struct {int nr; TYPE_3__** queue; } ;
struct combine_diff_path {char* path; struct combine_diff_path* next; TYPE_2__* parent; int /*<<< orphan*/  mode; int /*<<< orphan*/  oid; } ;
struct TYPE_8__ {char* path; int /*<<< orphan*/  mode; int /*<<< orphan*/  oid; } ;
struct TYPE_7__ {TYPE_1__* one; int /*<<< orphan*/  status; TYPE_4__* two; } ;
struct TYPE_6__ {int /*<<< orphan*/  path; int /*<<< orphan*/  status; int /*<<< orphan*/  mode; int /*<<< orphan*/  oid; } ;
struct TYPE_5__ {int /*<<< orphan*/  path; int /*<<< orphan*/  mode; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  combine_diff_path_size (int,int) ; 
 int compare_paths (struct combine_diff_path*,TYPE_4__*) ; 
 struct diff_queue_struct diff_queued_diff ; 
 scalar_t__ diff_unmodified_pair (TYPE_3__*) ; 
 scalar_t__ filename_changed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct combine_diff_path*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 struct combine_diff_path* xmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct combine_diff_path *intersect_paths(
	struct combine_diff_path *curr,
	int n,
	int num_parent,
	int combined_all_paths)
{
	struct diff_queue_struct *q = &diff_queued_diff;
	struct combine_diff_path *p, **tail = &curr;
	int i, j, cmp;

	if (!n) {
		for (i = 0; i < q->nr; i++) {
			int len;
			const char *path;
			if (diff_unmodified_pair(q->queue[i]))
				continue;
			path = q->queue[i]->two->path;
			len = strlen(path);
			p = xmalloc(combine_diff_path_size(num_parent, len));
			p->path = (char *) &(p->parent[num_parent]);
			memcpy(p->path, path, len);
			p->path[len] = 0;
			p->next = NULL;
			memset(p->parent, 0,
			       sizeof(p->parent[0]) * num_parent);

			oidcpy(&p->oid, &q->queue[i]->two->oid);
			p->mode = q->queue[i]->two->mode;
			oidcpy(&p->parent[n].oid, &q->queue[i]->one->oid);
			p->parent[n].mode = q->queue[i]->one->mode;
			p->parent[n].status = q->queue[i]->status;

			if (combined_all_paths &&
			    filename_changed(p->parent[n].status)) {
				strbuf_init(&p->parent[n].path, 0);
				strbuf_addstr(&p->parent[n].path,
					      q->queue[i]->one->path);
			}
			*tail = p;
			tail = &p->next;
		}
		return curr;
	}

	/*
	 * paths in curr (linked list) and q->queue[] (array) are
	 * both sorted in the tree order.
	 */
	i = 0;
	while ((p = *tail) != NULL) {
		cmp = ((i >= q->nr)
		       ? -1 : compare_paths(p, q->queue[i]->two));

		if (cmp < 0) {
			/* p->path not in q->queue[]; drop it */
			*tail = p->next;
			for (j = 0; j < num_parent; j++)
				if (combined_all_paths &&
				    filename_changed(p->parent[j].status))
					strbuf_release(&p->parent[j].path);
			free(p);
			continue;
		}

		if (cmp > 0) {
			/* q->queue[i] not in p->path; skip it */
			i++;
			continue;
		}

		oidcpy(&p->parent[n].oid, &q->queue[i]->one->oid);
		p->parent[n].mode = q->queue[i]->one->mode;
		p->parent[n].status = q->queue[i]->status;
		if (combined_all_paths &&
		    filename_changed(p->parent[n].status))
			strbuf_addstr(&p->parent[n].path,
				      q->queue[i]->one->path);

		tail = &p->next;
		i++;
	}
	return curr;
}
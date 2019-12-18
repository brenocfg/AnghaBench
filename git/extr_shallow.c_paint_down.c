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
typedef  unsigned int uint32_t ;
struct paint_info {int /*<<< orphan*/  ref_bitmap; int /*<<< orphan*/  nr_bits; } ;
struct object_id {int dummy; } ;
struct object {scalar_t__ type; int flags; } ;
struct commit_list {struct commit* item; struct commit_list* next; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; struct commit_list* parents; } ;

/* Variables and functions */
 int BOTTOM ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ OBJ_COMMIT ; 
 int SEEN ; 
 int UNINTERESTING ; 
 int /*<<< orphan*/  commit_list_insert (struct commit*,struct commit_list**) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (unsigned int*) ; 
 struct object* get_indexed_object (unsigned int) ; 
 unsigned int get_max_object_index () ; 
 struct commit* lookup_commit_reference_gently (int /*<<< orphan*/ ,struct object_id const*,int) ; 
 scalar_t__ memcmp (unsigned int*,unsigned int*,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,unsigned int*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 unsigned int* paint_alloc (struct paint_info*) ; 
 scalar_t__ parse_commit (struct commit*) ; 
 struct commit* pop_commit (struct commit_list**) ; 
 unsigned int** ref_bitmap_at (int /*<<< orphan*/ *,struct commit*) ; 
 size_t st_mult (int,int) ; 
 int /*<<< orphan*/  the_repository ; 
 unsigned int* xmalloc (size_t) ; 

__attribute__((used)) static void paint_down(struct paint_info *info, const struct object_id *oid,
		       unsigned int id)
{
	unsigned int i, nr;
	struct commit_list *head = NULL;
	int bitmap_nr = DIV_ROUND_UP(info->nr_bits, 32);
	size_t bitmap_size = st_mult(sizeof(uint32_t), bitmap_nr);
	struct commit *c = lookup_commit_reference_gently(the_repository, oid,
							  1);
	uint32_t *tmp; /* to be freed before return */
	uint32_t *bitmap;

	if (!c)
		return;

	tmp = xmalloc(bitmap_size);
	bitmap = paint_alloc(info);
	memset(bitmap, 0, bitmap_size);
	bitmap[id / 32] |= (1U << (id % 32));
	commit_list_insert(c, &head);
	while (head) {
		struct commit_list *p;
		struct commit *c = pop_commit(&head);
		uint32_t **refs = ref_bitmap_at(&info->ref_bitmap, c);

		/* XXX check "UNINTERESTING" from pack bitmaps if available */
		if (c->object.flags & (SEEN | UNINTERESTING))
			continue;
		else
			c->object.flags |= SEEN;

		if (*refs == NULL)
			*refs = bitmap;
		else {
			memcpy(tmp, *refs, bitmap_size);
			for (i = 0; i < bitmap_nr; i++)
				tmp[i] |= bitmap[i];
			if (memcmp(tmp, *refs, bitmap_size)) {
				*refs = paint_alloc(info);
				memcpy(*refs, tmp, bitmap_size);
			}
		}

		if (c->object.flags & BOTTOM)
			continue;

		if (parse_commit(c))
			die("unable to parse commit %s",
			    oid_to_hex(&c->object.oid));

		for (p = c->parents; p; p = p->next) {
			if (p->item->object.flags & SEEN)
				continue;
			commit_list_insert(p->item, &head);
		}
	}

	nr = get_max_object_index();
	for (i = 0; i < nr; i++) {
		struct object *o = get_indexed_object(i);
		if (o && o->type == OBJ_COMMIT)
			o->flags &= ~SEEN;
	}

	free(tmp);
}
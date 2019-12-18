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
struct blame_entry {struct blame_entry* next; int /*<<< orphan*/  suspect; } ;

/* Variables and functions */
 int /*<<< orphan*/  blame_origin_incref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct blame_entry*,struct blame_entry const*,int) ; 
 struct blame_entry* xmalloc (int) ; 

__attribute__((used)) static void add_blame_entry(struct blame_entry ***queue,
			    const struct blame_entry *src)
{
	struct blame_entry *e = xmalloc(sizeof(*e));
	memcpy(e, src, sizeof(*e));
	blame_origin_incref(e->suspect);

	e->next = **queue;
	**queue = e;
	*queue = &e->next;
}
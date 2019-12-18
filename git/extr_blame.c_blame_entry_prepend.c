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
struct blame_origin {int dummy; } ;
struct blame_entry {long lno; long num_lines; long s_lno; struct blame_entry* next; struct blame_origin* suspect; } ;

/* Variables and functions */
 int /*<<< orphan*/  blame_origin_incref (struct blame_origin*) ; 
 struct blame_entry* xcalloc (int,int) ; 

struct blame_entry *blame_entry_prepend(struct blame_entry *head,
					long start, long end,
					struct blame_origin *o)
{
	struct blame_entry *new_head = xcalloc(1, sizeof(struct blame_entry));
	new_head->lno = start;
	new_head->num_lines = end - start;
	new_head->suspect = o;
	new_head->s_lno = start;
	new_head->next = head;
	blame_origin_incref(o);
	return new_head;
}
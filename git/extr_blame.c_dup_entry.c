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
 int /*<<< orphan*/  blame_origin_decref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blame_origin_incref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct blame_entry*,struct blame_entry*,int) ; 

__attribute__((used)) static void dup_entry(struct blame_entry ***queue,
		      struct blame_entry *dst, struct blame_entry *src)
{
	blame_origin_incref(src->suspect);
	blame_origin_decref(dst->suspect);
	memcpy(dst, src, sizeof(*src));
	dst->next = **queue;
	**queue = dst;
	*queue = &dst->next;
}
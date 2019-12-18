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
typedef  void* uint64_t ;
struct rs_el {void* re_start; void* re_end; } ;
struct rangeset {int /*<<< orphan*/  rs_trie; } ;

/* Variables and functions */
 int pctrie_insert (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rangeset_check (struct rangeset*) ; 
 int rangeset_remove (struct rangeset*,void*,void*) ; 
 int /*<<< orphan*/  rs_node_alloc ; 

int
rangeset_insert(struct rangeset *rs, uint64_t start, uint64_t end,
    void *data)
{
	struct rs_el *r;
	int error;

	rangeset_check(rs);
	error = rangeset_remove(rs, start, end);
	if (error != 0)
		return (error);
	r = data;
	r->re_start = start;
	r->re_end = end;
	error = pctrie_insert(&rs->rs_trie, &r->re_start, rs_node_alloc);
	rangeset_check(rs);
	return (error);
}
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
struct revindex_entry {scalar_t__ offset; } ;
struct packed_git {int num_objects; struct revindex_entry* revindex; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 

int find_revindex_position(struct packed_git *p, off_t ofs)
{
	int lo = 0;
	int hi = p->num_objects + 1;
	const struct revindex_entry *revindex = p->revindex;

	do {
		const unsigned mi = lo + (hi - lo) / 2;
		if (revindex[mi].offset == ofs) {
			return mi;
		} else if (ofs < revindex[mi].offset)
			hi = mi;
		else
			lo = mi + 1;
	} while (lo < hi);

	error("bad offset for revindex");
	return -1;
}
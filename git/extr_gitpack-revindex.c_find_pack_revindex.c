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
struct revindex_entry {int dummy; } ;
struct packed_git {struct revindex_entry* revindex; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int find_revindex_position (struct packed_git*,int /*<<< orphan*/ ) ; 
 scalar_t__ load_pack_revindex (struct packed_git*) ; 

struct revindex_entry *find_pack_revindex(struct packed_git *p, off_t ofs)
{
	int pos;

	if (load_pack_revindex(p))
		return NULL;

	pos = find_revindex_position(p, ofs);

	if (pos < 0)
		return NULL;

	return p->revindex + pos;
}
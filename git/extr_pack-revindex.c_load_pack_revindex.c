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
struct packed_git {int /*<<< orphan*/  revindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  create_pack_revindex (struct packed_git*) ; 
 scalar_t__ open_pack_index (struct packed_git*) ; 

int load_pack_revindex(struct packed_git *p)
{
	if (!p->revindex) {
		if (open_pack_index(p))
			return -1;
		create_pack_revindex(p);
	}
	return 0;
}
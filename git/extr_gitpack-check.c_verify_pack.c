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
typedef  int /*<<< orphan*/  verify_fn ;
typedef  int /*<<< orphan*/  uint32_t ;
struct repository {int dummy; } ;
struct progress {int dummy; } ;
struct packed_git {int /*<<< orphan*/  index_data; } ;
struct pack_window {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  unuse_pack (struct pack_window**) ; 
 int verify_pack_index (struct packed_git*) ; 
 int verify_packfile (struct repository*,struct packed_git*,struct pack_window**,int /*<<< orphan*/ ,struct progress*,int /*<<< orphan*/ ) ; 

int verify_pack(struct repository *r, struct packed_git *p, verify_fn fn,
		struct progress *progress, uint32_t base_count)
{
	int err = 0;
	struct pack_window *w_curs = NULL;

	err |= verify_pack_index(p);
	if (!p->index_data)
		return -1;

	err |= verify_packfile(r, p, &w_curs, fn, progress, base_count);
	unuse_pack(&w_curs);

	return err;
}
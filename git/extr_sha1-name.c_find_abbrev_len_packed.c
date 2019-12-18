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
struct packed_git {struct packed_git* next; } ;
struct multi_pack_index {struct multi_pack_index* next; } ;
struct min_abbrev_data {int /*<<< orphan*/  repo; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_abbrev_len_for_midx (struct multi_pack_index*,struct min_abbrev_data*) ; 
 int /*<<< orphan*/  find_abbrev_len_for_pack (struct packed_git*,struct min_abbrev_data*) ; 
 struct multi_pack_index* get_multi_pack_index (int /*<<< orphan*/ ) ; 
 struct packed_git* get_packed_git (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void find_abbrev_len_packed(struct min_abbrev_data *mad)
{
	struct multi_pack_index *m;
	struct packed_git *p;

	for (m = get_multi_pack_index(mad->repo); m; m = m->next)
		find_abbrev_len_for_midx(m, mad);
	for (p = get_packed_git(mad->repo); p; p = p->next)
		find_abbrev_len_for_pack(p, mad);
}
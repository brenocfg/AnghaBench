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
typedef  int /*<<< orphan*/  u_int ;
struct rangeset {int /*<<< orphan*/  rs_alloc_flags; void* rs_data_ctx; int /*<<< orphan*/  rs_free_data; int /*<<< orphan*/  rs_dup_data; int /*<<< orphan*/  rs_trie; } ;
typedef  int /*<<< orphan*/  rs_free_data_t ;
typedef  int /*<<< orphan*/  rs_dup_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  pctrie_init (int /*<<< orphan*/ *) ; 

void
rangeset_init(struct rangeset *rs, rs_dup_data_t dup_data,
    rs_free_data_t free_data, void *data_ctx, u_int alloc_flags)
{

	pctrie_init(&rs->rs_trie);
	rs->rs_dup_data = dup_data;
	rs->rs_free_data = free_data;
	rs->rs_data_ctx = data_ctx;
	rs->rs_alloc_flags = alloc_flags;
}
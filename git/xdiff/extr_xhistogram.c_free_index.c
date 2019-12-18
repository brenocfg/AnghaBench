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
struct histindex {int /*<<< orphan*/  rcha; int /*<<< orphan*/  next_ptrs; int /*<<< orphan*/  line_map; int /*<<< orphan*/  records; } ;

/* Variables and functions */
 int /*<<< orphan*/  xdl_cha_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdl_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void free_index(struct histindex *index)
{
	xdl_free(index->records);
	xdl_free(index->line_map);
	xdl_free(index->next_ptrs);
	xdl_cha_free(&index->rcha);
}
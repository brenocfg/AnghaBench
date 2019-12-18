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
struct block {int dummy; } ;
typedef  int /*<<< orphan*/  block_head_t ;

/* Variables and functions */
 struct block* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (struct block*) ; 

__attribute__((used)) static void
free_block(block_head_t *pbh)
{
	struct block *ptr;

	while ((ptr = TAILQ_FIRST(pbh))) {
		TAILQ_REMOVE(pbh, ptr, entry);
		free(ptr);
	}
}
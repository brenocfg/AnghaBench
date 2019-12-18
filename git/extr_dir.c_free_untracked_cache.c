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
struct untracked_cache {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct untracked_cache*) ; 
 int /*<<< orphan*/  free_untracked (int /*<<< orphan*/ ) ; 

void free_untracked_cache(struct untracked_cache *uc)
{
	if (uc)
		free_untracked(uc->root);
	free(uc);
}
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
struct merge_remote_desc {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  merge_desc_slab ; 
 struct merge_remote_desc** merge_desc_slab_at (int /*<<< orphan*/ *,struct commit*) ; 

struct merge_remote_desc *merge_remote_util(struct commit *commit)
{
	return *merge_desc_slab_at(&merge_desc_slab, commit);
}
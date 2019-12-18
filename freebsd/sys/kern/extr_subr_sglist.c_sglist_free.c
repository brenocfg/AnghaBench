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
struct sglist {int /*<<< orphan*/  sg_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SGLIST ; 
 int /*<<< orphan*/  free (struct sglist*,int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 

void
sglist_free(struct sglist *sg)
{

	if (sg == NULL)
		return;

	if (refcount_release(&sg->sg_refs))
		free(sg, M_SGLIST);
}
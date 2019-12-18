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
struct knlist {int kl_autodestroy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNL_ASSERT_LOCKED (struct knlist*) ; 
 int /*<<< orphan*/  M_KQUEUE ; 
 int /*<<< orphan*/  free (struct knlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_destroy (struct knlist*) ; 
 scalar_t__ knlist_empty (struct knlist*) ; 

void
knlist_detach(struct knlist *knl)
{

	KNL_ASSERT_LOCKED(knl);
	knl->kl_autodestroy = 1;
	if (knlist_empty(knl)) {
		knlist_destroy(knl);
		free(knl, M_KQUEUE);
	}
}
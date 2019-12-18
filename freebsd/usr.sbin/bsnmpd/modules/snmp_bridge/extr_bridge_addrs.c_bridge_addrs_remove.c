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
struct tp_entry {int dummy; } ;
struct bridge_if {struct tp_entry* f_tpa; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct tp_entry*,int /*<<< orphan*/ ) ; 
 struct tp_entry* bridge_addrs_bif_next (struct tp_entry*) ; 
 int /*<<< orphan*/  free (struct tp_entry*) ; 
 int /*<<< orphan*/  tp_e ; 
 int /*<<< orphan*/  tp_entries ; 

void
bridge_addrs_remove(struct tp_entry *te, struct bridge_if *bif)
{
	if (bif->f_tpa == te)
		bif->f_tpa = bridge_addrs_bif_next(te);

	TAILQ_REMOVE(&tp_entries, te, tp_e);
	free(te);
}
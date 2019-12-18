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
struct tp_entries {int dummy; } ;

/* Variables and functions */
 struct tp_entry* TAILQ_FIRST (struct tp_entries*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct tp_entries*,struct tp_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct tp_entry*) ; 
 int /*<<< orphan*/  tp_e ; 

__attribute__((used)) static void
bridge_tpe_free(struct tp_entries *headp)
{
	struct tp_entry *t;

	while ((t = TAILQ_FIRST(headp)) != NULL) {
		TAILQ_REMOVE(headp, t, tp_e);
		free(t);
	}
}
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
struct tp_entry {scalar_t__ sysindex; } ;

/* Variables and functions */
 struct tp_entry* TAILQ_NEXT (struct tp_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tp_e ; 

struct tp_entry *
bridge_addrs_bif_next(struct tp_entry *te)
{
	struct tp_entry *te_next;

	if ((te_next = TAILQ_NEXT(te, tp_e)) == NULL ||
	    te_next->sysindex != te->sysindex)
		return (NULL);

	return (te_next);
}
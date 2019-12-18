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
struct dn_fsk_head {int dummy; } ;
struct dn_fsk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND (char*,int,...) ; 
 struct dn_fsk* SLIST_FIRST (struct dn_fsk_head*) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (struct dn_fsk_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsk_detach (struct dn_fsk*,int) ; 
 int /*<<< orphan*/  sch_chain ; 

__attribute__((used)) static void
fsk_detach_list(struct dn_fsk_head *h, int flags)
{
	struct dn_fsk *fs;
	int n = 0; /* only for stats */

	ND("head %p flags %x", h, flags);
	while ((fs = SLIST_FIRST(h))) {
		SLIST_REMOVE_HEAD(h, sch_chain);
		n++;
		fsk_detach(fs, flags);
	}
	ND("done %d flowsets", n);
}
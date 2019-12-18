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
struct pfr_table {int /*<<< orphan*/  pfrt_anchor; } ;
struct pfr_ktable {int /*<<< orphan*/  pfrkt_anchor; } ;

/* Variables and functions */
 int PFR_FLAG_ALLRSETS ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pfr_skip_table(struct pfr_table *filter, struct pfr_ktable *kt, int flags)
{
	if (flags & PFR_FLAG_ALLRSETS)
		return (0);
	if (strcmp(filter->pfrt_anchor, kt->pfrkt_anchor))
		return (1);
	return (0);
}
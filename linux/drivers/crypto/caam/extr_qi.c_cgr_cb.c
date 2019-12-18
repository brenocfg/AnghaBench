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
struct qman_portal {int dummy; } ;
struct qman_cgr {int dummy; } ;

/* Variables and functions */
 int caam_congested ; 
 int /*<<< orphan*/  pr_debug_ratelimited (char*) ; 
 int /*<<< orphan*/  times_congested ; 

__attribute__((used)) static void cgr_cb(struct qman_portal *qm, struct qman_cgr *cgr, int congested)
{
	caam_congested = congested;

	if (congested) {
#ifdef CONFIG_DEBUG_FS
		times_congested++;
#endif
		pr_debug_ratelimited("CAAM entered congestion\n");

	} else {
		pr_debug_ratelimited("CAAM exited congestion\n");
	}
}
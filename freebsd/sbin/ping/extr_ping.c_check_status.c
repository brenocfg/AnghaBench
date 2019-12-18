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

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 double nreceived ; 
 double nrepeats ; 
 int ntransmitted ; 
 scalar_t__ siginfo_p ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ timing ; 
 double tmax ; 
 double tmin ; 
 double tsum ; 

__attribute__((used)) static void
check_status(void)
{

	if (siginfo_p) {
		siginfo_p = 0;
		(void)fprintf(stderr, "\r%ld/%ld packets received (%.1f%%)",
		    nreceived, ntransmitted,
		    ntransmitted ? nreceived * 100.0 / ntransmitted : 0.0);
		if (nreceived && timing)
			(void)fprintf(stderr, " %.3f min / %.3f avg / %.3f max",
			    tmin, tsum / (nreceived + nrepeats), tmax);
		(void)fprintf(stderr, "\n");
	}
}
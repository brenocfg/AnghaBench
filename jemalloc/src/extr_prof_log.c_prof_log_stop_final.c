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
typedef  int /*<<< orphan*/  tsd_t ;

/* Variables and functions */
 int /*<<< orphan*/  prof_log_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tsd_fetch () ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
prof_log_stop_final(void) {
	tsd_t *tsd = tsd_fetch();
	prof_log_stop(tsd_tsdn(tsd));
}
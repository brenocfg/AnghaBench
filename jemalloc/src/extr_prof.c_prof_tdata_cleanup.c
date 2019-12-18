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
typedef  int /*<<< orphan*/  prof_tdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  config_prof ; 
 int /*<<< orphan*/  prof_tdata_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tsd_prof_tdata_get (int /*<<< orphan*/ *) ; 

void
prof_tdata_cleanup(tsd_t *tsd) {
	prof_tdata_t *tdata;

	if (!config_prof) {
		return;
	}

	tdata = tsd_prof_tdata_get(tsd);
	if (tdata != NULL) {
		prof_tdata_detach(tsd, tdata);
	}
}
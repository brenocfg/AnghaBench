#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_6__ {int active; int /*<<< orphan*/ * thread_name; scalar_t__ thr_discrim; scalar_t__ thr_uid; } ;
typedef  TYPE_1__ prof_tdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  prof_tdata_detach (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* prof_tdata_init_impl (int /*<<< orphan*/ *,scalar_t__,scalar_t__,char*,int,int) ; 
 char* prof_thread_name_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

prof_tdata_t *
prof_tdata_reinit(tsd_t *tsd, prof_tdata_t *tdata) {
	uint64_t thr_uid = tdata->thr_uid;
	uint64_t thr_discrim = tdata->thr_discrim + 1;
	char *thread_name = (tdata->thread_name != NULL) ?
	    prof_thread_name_alloc(tsd_tsdn(tsd), tdata->thread_name) : NULL;
	bool active = tdata->active;

	prof_tdata_detach(tsd, tdata);
	return prof_tdata_init_impl(tsd, thr_uid, thr_discrim, thread_name,
	    active, true);
}
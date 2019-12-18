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
 int /*<<< orphan*/ * prof_tdata_init_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prof_thr_uid_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prof_thread_active_init_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

prof_tdata_t *
prof_tdata_init(tsd_t *tsd) {
	return prof_tdata_init_impl(tsd, prof_thr_uid_alloc(tsd_tsdn(tsd)), 0,
	    NULL, prof_thread_active_init_get(tsd_tsdn(tsd)), false);
}
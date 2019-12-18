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
typedef  int /*<<< orphan*/  prof_bt_t ;

/* Variables and functions */
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_prof ; 
 int /*<<< orphan*/  post_reentrancy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pre_reentrancy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_backtrace_impl (int /*<<< orphan*/ *) ; 

void
prof_backtrace(tsd_t *tsd, prof_bt_t *bt) {
	cassert(config_prof);
	pre_reentrancy(tsd, NULL);
	prof_backtrace_impl(bt);
	post_reentrancy(tsd);
}
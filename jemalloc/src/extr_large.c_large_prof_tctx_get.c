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
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  prof_tctx_t ;
typedef  int /*<<< orphan*/  extent_t ;

/* Variables and functions */
 int /*<<< orphan*/ * extent_prof_tctx_get (int /*<<< orphan*/  const*) ; 

prof_tctx_t *
large_prof_tctx_get(tsdn_t *tsdn, const extent_t *extent) {
	return extent_prof_tctx_get(extent);
}
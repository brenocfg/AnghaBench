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
typedef  int /*<<< orphan*/  extent_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 size_t LG_PAGE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atomic_fetch_sub_zu (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 size_t atomic_load_zu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_prof ; 
 int /*<<< orphan*/  curpages ; 
 size_t extent_size_get (int /*<<< orphan*/  const*) ; 
 scalar_t__ extent_state_active ; 
 scalar_t__ extent_state_get (int /*<<< orphan*/  const*) ; 
 scalar_t__ opt_prof ; 

__attribute__((used)) static void
extent_gdump_sub(tsdn_t *tsdn, const extent_t *extent) {
	cassert(config_prof);

	if (opt_prof && extent_state_get(extent) == extent_state_active) {
		size_t nsub = extent_size_get(extent) >> LG_PAGE;
		assert(atomic_load_zu(&curpages, ATOMIC_RELAXED) >= nsub);
		atomic_fetch_sub_zu(&curpages, nsub, ATOMIC_RELAXED);
	}
}
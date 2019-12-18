#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ dss_prec_t ;
struct TYPE_3__ {int /*<<< orphan*/  dss_prec; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELEASE ; 
 int /*<<< orphan*/  atomic_store_u (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dss_prec_disabled ; 
 int /*<<< orphan*/  have_dss ; 

bool
arena_dss_prec_set(arena_t *arena, dss_prec_t dss_prec) {
	if (!have_dss) {
		return (dss_prec != dss_prec_disabled);
	}
	atomic_store_u(&arena->dss_prec, (unsigned)dss_prec, ATOMIC_RELEASE);
	return false;
}
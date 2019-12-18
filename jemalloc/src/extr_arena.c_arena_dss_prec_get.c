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
typedef  int /*<<< orphan*/  dss_prec_t ;
struct TYPE_3__ {int /*<<< orphan*/  dss_prec; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_ACQUIRE ; 
 int /*<<< orphan*/  atomic_load_u (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

dss_prec_t
arena_dss_prec_get(arena_t *arena) {
	return (dss_prec_t)atomic_load_u(&arena->dss_prec, ATOMIC_ACQUIRE);
}
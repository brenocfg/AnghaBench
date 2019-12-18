#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int initialized; } ;
typedef  TYPE_1__ sc_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  LG_PAGE ; 
 int /*<<< orphan*/  LG_QUANTUM ; 
 int /*<<< orphan*/  LG_SIZEOF_PTR ; 
 int /*<<< orphan*/  SC_LG_TINY_MIN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  size_classes (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

void
sc_data_init(sc_data_t *sc_data) {
	assert(!sc_data->initialized);

	int lg_max_lookup = 12;

	size_classes(sc_data, LG_SIZEOF_PTR, LG_QUANTUM, SC_LG_TINY_MIN,
	    lg_max_lookup, LG_PAGE, 2);

	sc_data->initialized = true;
}
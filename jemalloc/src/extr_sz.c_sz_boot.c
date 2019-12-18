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
typedef  int /*<<< orphan*/  sc_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  sz_boot_index2size_tab (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sz_boot_pind2sz_tab (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sz_boot_size2index_tab (int /*<<< orphan*/  const*) ; 

void
sz_boot(const sc_data_t *sc_data) {
	sz_boot_pind2sz_tab(sc_data);
	sz_boot_index2size_tab(sc_data);
	sz_boot_size2index_tab(sc_data);
}
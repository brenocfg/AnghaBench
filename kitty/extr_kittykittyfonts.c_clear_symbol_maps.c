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

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ num_symbol_maps ; 
 int /*<<< orphan*/ * symbol_maps ; 

__attribute__((used)) static inline void
clear_symbol_maps() {
    if (symbol_maps) { free(symbol_maps); symbol_maps = NULL; num_symbol_maps = 0; }
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  aux_mux_enabled; } ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* kbdcp (int /*<<< orphan*/ ) ; 
 int set_aux_mux_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
disable_aux_mux(KBDC p)
{

	kbdcp(p)->aux_mux_enabled = FALSE;

	return (set_aux_mux_state(p, FALSE));
}
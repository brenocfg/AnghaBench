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
struct TYPE_2__ {int aux_mux_port; } ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int FALSE ; 
 int KBDC_AUX_MUX_NUM_PORTS ; 
 int TRUE ; 
 int /*<<< orphan*/  aux_mux_is_enabled (int /*<<< orphan*/ ) ; 
 TYPE_1__* kbdcp (int /*<<< orphan*/ ) ; 

int
set_active_aux_mux_port(KBDC p, int port)
{

	if (!aux_mux_is_enabled(p))
		return (FALSE);

	if (port < 0 || port >= KBDC_AUX_MUX_NUM_PORTS)
		return (FALSE);

	kbdcp(p)->aux_mux_port = port;

	return (TRUE);
}
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
 int KBDC_WRITE_TO_AUX ; 
 int KBDC_WRITE_TO_AUX_MUX ; 
 scalar_t__ aux_mux_is_enabled (int /*<<< orphan*/ ) ; 
 TYPE_1__* kbdcp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_controller_command (int /*<<< orphan*/ ,int) ; 
 int write_controller_data (int /*<<< orphan*/ ,int) ; 

int
write_aux_command(KBDC p, int c)
{
    int f;

    f = aux_mux_is_enabled(p) ?
        KBDC_WRITE_TO_AUX_MUX + kbdcp(p)->aux_mux_port : KBDC_WRITE_TO_AUX;

    if (!write_controller_command(p, f))
	return FALSE;
    return write_controller_data(p, c);
}
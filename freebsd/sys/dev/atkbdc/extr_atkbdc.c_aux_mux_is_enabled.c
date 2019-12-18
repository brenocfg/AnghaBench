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
struct TYPE_2__ {int aux_mux_enabled; } ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 TYPE_1__* kbdcp (int /*<<< orphan*/ ) ; 

int
aux_mux_is_enabled(KBDC p)
{

	return (kbdcp(p)->aux_mux_enabled);
}
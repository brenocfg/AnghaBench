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
 int /*<<< orphan*/  init_network () ; 
 int /*<<< orphan*/  init_sys () ; 
 int /*<<< orphan*/  init_telnet () ; 
 int /*<<< orphan*/  init_terminal () ; 

void
tninit(void)
{
    init_terminal();

    init_network();

    init_telnet();

    init_sys();
}
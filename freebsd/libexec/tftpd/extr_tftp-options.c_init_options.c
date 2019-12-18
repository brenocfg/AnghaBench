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
struct TYPE_2__ {int /*<<< orphan*/  o_request; } ;

/* Variables and functions */
 size_t OPT_ROLLOVER ; 
 TYPE_1__* options ; 
 int /*<<< orphan*/  strdup (char*) ; 

void
init_options(void)
{

	options[OPT_ROLLOVER].o_request = strdup("0");
}
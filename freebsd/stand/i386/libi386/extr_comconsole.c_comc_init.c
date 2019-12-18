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
struct TYPE_2__ {int c_flags; } ;

/* Variables and functions */
 int CMD_ERROR ; 
 int CMD_OK ; 
 int C_PRESENTIN ; 
 int C_PRESENTOUT ; 
 int /*<<< orphan*/  comc_curspeed ; 
 int /*<<< orphan*/  comc_port ; 
 int /*<<< orphan*/  comc_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ comconsole ; 

__attribute__((used)) static int
comc_init(int arg)
{

	comc_setup(comc_curspeed, comc_port);

	if ((comconsole.c_flags & (C_PRESENTIN | C_PRESENTOUT)) ==
	    (C_PRESENTIN | C_PRESENTOUT))
		return (CMD_OK);
	return (CMD_ERROR);
}
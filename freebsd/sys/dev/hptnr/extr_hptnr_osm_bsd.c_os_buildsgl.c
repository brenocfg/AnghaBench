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
typedef  int /*<<< orphan*/  PSG ;
typedef  int /*<<< orphan*/  PCOMMAND ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  HPT_ASSERT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int os_buildsgl(PCOMMAND pCmd, PSG pSg, int logical)
{
	/* since we have provided physical sg, nobody will ask us to build physical sg */
	HPT_ASSERT(0);
	return FALSE;
}
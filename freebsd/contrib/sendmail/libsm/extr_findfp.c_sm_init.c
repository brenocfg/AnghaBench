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
struct TYPE_2__ {int /*<<< orphan*/ * sm_magic; int /*<<< orphan*/ * f_type; } ;

/* Variables and functions */
 int Sm_IO_DidInit ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 TYPE_1__ empty ; 
 int /*<<< orphan*/  sm_cleanup ; 

void
sm_init()
{
	if (Sm_IO_DidInit)	/* paranoia */
		return;

	/* more paranoia: initialize pointers in a static variable */
	empty.f_type = NULL;
	empty.sm_magic = NULL;

	/* make sure we clean up on exit */
	atexit(sm_cleanup);		/* conservative */
	Sm_IO_DidInit = true;
}
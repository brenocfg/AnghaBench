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
 int /*<<< orphan*/  DCONS_CON ; 
 int /*<<< orphan*/  DCONS_GDB ; 
 int /*<<< orphan*/  DC_GDB ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dcons_attach_port (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcons_callout ; 
 int /*<<< orphan*/  dcons_timeout ; 
 int hz ; 
 int poll_hz ; 

__attribute__((used)) static int
dcons_attach(void)
{
	int polltime;

	dcons_attach_port(DCONS_CON, "dcons", 0);
	dcons_attach_port(DCONS_GDB, "dgdb", DC_GDB);
	callout_init(&dcons_callout, 1);
	polltime = hz / poll_hz;
	callout_reset(&dcons_callout, polltime, dcons_timeout, NULL);
	return(0);
}
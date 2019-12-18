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
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DEBUGOUT (char*) ; 
 int ixgbe_setup_low_power_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ixgbe_if_shutdown(if_ctx_t ctx)
{
	int error = 0;

	INIT_DEBUGOUT("ixgbe_shutdown: begin");

	error = ixgbe_setup_low_power_mode(ctx);

	return (error);
}
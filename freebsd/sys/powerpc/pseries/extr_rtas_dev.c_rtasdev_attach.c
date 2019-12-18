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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_LAST ; 
 int /*<<< orphan*/  clock_register (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtas_shutdown ; 
 int rtas_token_lookup (char*) ; 
 int /*<<< orphan*/  shutdown_final ; 

__attribute__((used)) static int
rtasdev_attach(device_t dev)
{
	if (rtas_token_lookup("get-time-of-day") != -1)
		clock_register(dev, 2000);
	
	EVENTHANDLER_REGISTER(shutdown_final, rtas_shutdown, NULL,
	    SHUTDOWN_PRI_LAST);

	return (0);
}
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
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 int /*<<< orphan*/  UI_LAN_UPDATEVISIBLEPINGS ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int) ; 

qboolean trap_LAN_UpdateVisiblePings( int source ) {
	return syscall( UI_LAN_UPDATEVISIBLEPINGS, source );
}
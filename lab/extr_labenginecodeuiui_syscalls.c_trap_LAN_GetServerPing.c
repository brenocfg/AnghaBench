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
 int /*<<< orphan*/  UI_LAN_GETSERVERPING ; 
 int syscall (int /*<<< orphan*/ ,int,int) ; 

int trap_LAN_GetServerPing( int source, int n ) {
	return syscall( UI_LAN_GETSERVERPING, source, n );
}
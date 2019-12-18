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
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CLOCK_DBG_READ ; 
 int /*<<< orphan*/  clock_print_ts (struct timespec*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  getnanotime (struct timespec*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
clock_dbgprint_hdr(device_t dev, int rw)
{
	struct timespec now;

	getnanotime(&now);
	device_printf(dev, "%s at ", (rw & CLOCK_DBG_READ) ? "read " : "write");
	clock_print_ts(&now, 9);
	printf(": "); 
}
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
 int /*<<< orphan*/  PRVERBOSE (char*,int,int,int) ; 
 int ppb_rdtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wdtr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ppstry(device_t ppbus, int send, int expect)
{
	int i;

	ppb_wdtr(ppbus, send);
	i = ppb_rdtr(ppbus);
	PRVERBOSE("S: %02x E: %02x G: %02x\n", send, expect, i);
	return (i != expect);
}
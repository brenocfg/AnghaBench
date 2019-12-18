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
typedef  int /*<<< orphan*/  uint64_t ;
struct ifnet {int /*<<< orphan*/  if_baudrate; } ;

/* Variables and functions */

uint64_t
if_setbaudrate(struct ifnet *ifp, uint64_t baudrate)
{
	uint64_t oldbrate;

	oldbrate = ifp->if_baudrate;
	ifp->if_baudrate = baudrate;
	return (oldbrate);
}
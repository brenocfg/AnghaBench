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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packet_trace (char*,int,int) ; 
 scalar_t__ write_in_full (int,char*,int) ; 

void packet_delim(int fd)
{
	packet_trace("0001", 4, 1);
	if (write_in_full(fd, "0001", 4) < 0)
		die_errno(_("unable to write delim packet"));
}
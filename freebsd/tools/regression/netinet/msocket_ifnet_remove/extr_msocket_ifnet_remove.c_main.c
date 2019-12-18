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
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 scalar_t__ test_sock_type (int /*<<< orphan*/ ,char*) ; 

int
main(int argc, char *argv[])
{

	if (test_sock_type(SOCK_RAW, "SOCK_RAW") < 0)
		return (-1);

	if (test_sock_type(SOCK_DGRAM, "SOCK_DGRAM") < 0)
		return (-1);

	return (0);
}
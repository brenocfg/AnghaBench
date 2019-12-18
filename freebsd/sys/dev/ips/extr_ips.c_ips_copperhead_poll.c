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
typedef  int /*<<< orphan*/  ips_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

void ips_copperhead_poll(ips_command_t *command)
{

	printf("ips: cmd polling not implemented for copperhead devices\n");
}
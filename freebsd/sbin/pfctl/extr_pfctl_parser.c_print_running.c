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
struct pf_status {scalar_t__ running; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*) ; 

void
print_running(struct pf_status *status)
{
	printf("%s\n", status->running ? "Enabled" : "Disabled");
}
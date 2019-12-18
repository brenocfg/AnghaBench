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
struct itimerval {int /*<<< orphan*/  it_value; int /*<<< orphan*/  it_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktrtimeval (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

void
ktritimerval(struct itimerval *it)
{

	printf("itimerval { .interval = ");
	ktrtimeval(&it->it_interval);
	printf(", .value = ");
	ktrtimeval(&it->it_value);
	printf(" }\n");
}
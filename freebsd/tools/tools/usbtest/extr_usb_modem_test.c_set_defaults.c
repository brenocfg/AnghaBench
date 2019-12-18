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
struct modem {int data_stress_test; int control_ep_test; int duration; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct modem*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
set_defaults(struct modem *p)
{
	memset(p, 0, sizeof(*p));

	p->data_stress_test = 1;
	p->control_ep_test = 1;
	p->duration = 60;		/* seconds */
}
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
typedef  int /*<<< orphan*/  u_int ;
struct uart_class {int /*<<< orphan*/  uc_riowidth; } ;

/* Variables and functions */

u_int
uart_getregiowidth(struct uart_class *uc)
{
	return ((uc != NULL) ? uc->uc_riowidth : 0);
}
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
struct consdev {int /*<<< orphan*/  cn_arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  uart_grab (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uart_cngrab(struct consdev *cp)
{

	uart_grab(cp->cn_arg);
}
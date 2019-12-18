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
 int /*<<< orphan*/  AT93C_WENCMD ; 
 int /*<<< orphan*/  at93c_end_op () ; 
 int /*<<< orphan*/  at93c_init_op () ; 
 int /*<<< orphan*/  at93c_write_bits (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void at93c_disable_wp(void)
{
	at93c_init_op();
	at93c_write_bits(AT93C_WENCMD, 10);
	at93c_end_op();
}
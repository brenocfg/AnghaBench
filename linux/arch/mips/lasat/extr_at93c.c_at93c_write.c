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
typedef  int u8 ;

/* Variables and functions */
 int AT93C_ADDR_MAX ; 
 int AT93C_WCMD ; 
 int /*<<< orphan*/  at93c_disable_wp () ; 
 int /*<<< orphan*/  at93c_enable_wp () ; 
 int /*<<< orphan*/  at93c_end_op () ; 
 int /*<<< orphan*/  at93c_init_op () ; 
 int /*<<< orphan*/  at93c_wait () ; 
 int /*<<< orphan*/  at93c_write_bits (int,int) ; 

void at93c_write(u8 addr, u8 data)
{
	at93c_disable_wp();
	at93c_init_op();
	at93c_write_bits((addr & AT93C_ADDR_MAX)|AT93C_WCMD, 10);
	at93c_write_bits(data, 8);
	at93c_end_op();
	at93c_wait();
	at93c_enable_wp();
}
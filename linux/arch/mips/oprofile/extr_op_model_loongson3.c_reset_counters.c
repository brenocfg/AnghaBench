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
 int /*<<< orphan*/  write_c0_perfhi1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_perfhi2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_perflo1 (int) ; 
 int /*<<< orphan*/  write_c0_perflo2 (int) ; 

__attribute__((used)) static void reset_counters(void *arg)
{
	write_c0_perfhi1(0);
	write_c0_perfhi2(0);
	write_c0_perflo1(0xc0000000);
	write_c0_perflo2(0x40000000);
}
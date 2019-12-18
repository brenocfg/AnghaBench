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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int kvm_counter_u64_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmd ; 
 scalar_t__ kvmd_init () ; 

uint64_t
kread_counter(u_long addr)
{

	if (kvmd_init() < 0)
		return (-1);

	return (kvm_counter_u64_fetch(kvmd, addr));
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long sas_ss_sp; unsigned long sas_ss_size; } ;

/* Variables and functions */
 TYPE_1__* current ; 

__attribute__((used)) static inline int
rbs_on_sig_stack (unsigned long bsp)
{
	return (bsp - current->sas_ss_sp < current->sas_ss_size);
}
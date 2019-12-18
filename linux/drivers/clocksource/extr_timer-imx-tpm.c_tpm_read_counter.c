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
 scalar_t__ TPM_CNT ; 
 unsigned long readl (scalar_t__) ; 
 scalar_t__ timer_base ; 

__attribute__((used)) static inline unsigned long tpm_read_counter(void)
{
	return readl(timer_base + TPM_CNT);
}
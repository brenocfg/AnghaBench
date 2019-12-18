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
typedef  int u64 ;

/* Variables and functions */
 int IOAT_CHANSTS_COMPLETED_DESCRIPTOR_ADDR ; 

__attribute__((used)) static inline u64 ioat_chansts_to_addr(u64 status)
{
	return status & IOAT_CHANSTS_COMPLETED_DESCRIPTOR_ADDR;
}
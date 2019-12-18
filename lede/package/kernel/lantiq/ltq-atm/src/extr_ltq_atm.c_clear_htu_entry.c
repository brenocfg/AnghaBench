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
struct TYPE_2__ {scalar_t__ vld; } ;

/* Variables and functions */
 TYPE_1__* HTU_ENTRY (scalar_t__) ; 
 scalar_t__ OAM_HTU_ENTRY_NUMBER ; 

__attribute__((used)) static inline void clear_htu_entry(unsigned int queue)
{
	HTU_ENTRY(queue + OAM_HTU_ENTRY_NUMBER)->vld = 0;
}
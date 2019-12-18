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
typedef  int pt_entry_t ;

/* Variables and functions */
 int ATTR_DESCR_MASK ; 
 int L3_PAGE ; 

__attribute__((used)) static __inline int
pmap_l3_valid(pt_entry_t l3)
{

	return ((l3 & ATTR_DESCR_MASK) == L3_PAGE);
}
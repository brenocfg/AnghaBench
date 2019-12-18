#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_3__ {size_t* srcdest_pairs; } ;
typedef  TYPE_1__ cdg_link_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t get_next_srcdest_pair(cdg_link_t * link, uint32_t index)
{
	return link->srcdest_pairs[index];
}
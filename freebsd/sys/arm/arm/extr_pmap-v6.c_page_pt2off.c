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
typedef  int u_int ;

/* Variables and functions */
 int NB_IN_PT2 ; 
 int PT2PG_MASK ; 

__attribute__((used)) static __inline u_int
page_pt2off(u_int pt1_idx)
{

	return ((pt1_idx & PT2PG_MASK) * NB_IN_PT2);
}
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
struct cppi41_desc {int pd0; } ;

/* Variables and functions */
 int DESC_TYPE ; 
 int DESC_TYPE_TEARD ; 

__attribute__((used)) static void cppi41_compute_td_desc(struct cppi41_desc *d)
{
	d->pd0 = DESC_TYPE_TEARD << DESC_TYPE;
}
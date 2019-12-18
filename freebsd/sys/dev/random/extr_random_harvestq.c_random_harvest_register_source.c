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
typedef  enum random_entropy_source { ____Placeholder_random_entropy_source } random_entropy_source ;

/* Variables and functions */
 int hc_source_mask ; 

void
random_harvest_register_source(enum random_entropy_source source)
{

	hc_source_mask |= (1 << source);
}
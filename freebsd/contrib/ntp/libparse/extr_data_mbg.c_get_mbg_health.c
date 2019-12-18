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
typedef  scalar_t__ HEALTH ;

/* Variables and functions */
 scalar_t__ get_lsb_short (unsigned char**) ; 

void
get_mbg_health(
	unsigned char **bufpp,
	HEALTH *healthp
	)
{
  *healthp = (HEALTH) get_lsb_short(bufpp);
}
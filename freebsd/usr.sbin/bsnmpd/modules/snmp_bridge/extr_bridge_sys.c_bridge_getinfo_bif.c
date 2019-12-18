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
struct bridge_if {int dummy; } ;

/* Variables and functions */
 scalar_t__ bridge_get_conf_param (struct bridge_if*) ; 
 int bridge_get_op_param (struct bridge_if*) ; 

int
bridge_getinfo_bif(struct bridge_if *bif)
{
	if (bridge_get_conf_param(bif) < 0)
		return (-1);

	return (bridge_get_op_param(bif));
}
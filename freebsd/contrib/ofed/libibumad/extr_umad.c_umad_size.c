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
struct ib_user_mad {int dummy; } ;

/* Variables and functions */
 scalar_t__ new_user_mad_api ; 

size_t umad_size(void)
{
	return new_user_mad_api ? sizeof(struct ib_user_mad) :
	    sizeof(struct ib_user_mad) - 8;
}
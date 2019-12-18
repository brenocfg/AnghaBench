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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 

int
inet6_opt_get_val(void *databuf, int offset, void *val, socklen_t vallen)
{

	/* we can't assume alignment here */
	memcpy(val, (u_int8_t *)databuf + offset, vallen);

	return(offset + vallen);
}
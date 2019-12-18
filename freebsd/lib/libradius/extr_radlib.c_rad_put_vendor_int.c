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
typedef  int /*<<< orphan*/  u_int32_t ;
struct rad_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int rad_put_vendor_attr (struct rad_handle*,int,int,int /*<<< orphan*/ *,int) ; 

int
rad_put_vendor_int(struct rad_handle *h, int vendor, int type, u_int32_t i)
{
	u_int32_t value;

	value = htonl(i);
	return (rad_put_vendor_attr(h, vendor, type, &value, sizeof value));
}
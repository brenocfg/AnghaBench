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
struct rad_handle {int dummy; } ;

/* Variables and functions */
 int rad_put_vendor_attr (struct rad_handle*,int,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int
rad_put_vendor_string(struct rad_handle *h, int vendor, int type,
    const char *str)
{
	return (rad_put_vendor_attr(h, vendor, type, str, strlen(str)));
}
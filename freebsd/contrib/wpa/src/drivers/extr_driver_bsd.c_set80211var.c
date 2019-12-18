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
struct bsd_driver_data {int dummy; } ;

/* Variables and functions */
 int bsd_set80211 (struct bsd_driver_data*,int,int /*<<< orphan*/ ,void const*,int) ; 

__attribute__((used)) static int
set80211var(struct bsd_driver_data *drv, int op, const void *arg, int arg_len)
{
	return bsd_set80211(drv, op, 0, arg, arg_len);
}
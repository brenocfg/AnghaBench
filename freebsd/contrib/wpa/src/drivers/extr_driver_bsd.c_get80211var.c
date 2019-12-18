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
struct ieee80211req {int i_len; } ;
struct bsd_driver_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ bsd_get80211 (struct bsd_driver_data*,struct ieee80211req*,int,void*,int) ; 

__attribute__((used)) static int
get80211var(struct bsd_driver_data *drv, int op, void *arg, int arg_len)
{
	struct ieee80211req ireq;

	if (bsd_get80211(drv, &ireq, op, arg, arg_len) < 0)
		return -1;
	return ireq.i_len;
}
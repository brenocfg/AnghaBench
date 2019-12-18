#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ieee80211req {int i_type; int i_val; int i_len; void* i_data; int /*<<< orphan*/  i_name; } ;
struct bsd_driver_data {scalar_t__ ifindex; TYPE_1__* global; int /*<<< orphan*/  ifname; scalar_t__ if_removed; } ;
typedef  int /*<<< orphan*/  ireq ;
struct TYPE_2__ {int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  SIOCS80211 ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211req*) ; 
 int /*<<< orphan*/  os_memset (struct ieee80211req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bsd_set80211(void *priv, int op, int val, const void *arg, int arg_len)
{
	struct bsd_driver_data *drv = priv;
	struct ieee80211req ireq;

	if (drv->ifindex == 0 || drv->if_removed)
		return -1;

	os_memset(&ireq, 0, sizeof(ireq));
	os_strlcpy(ireq.i_name, drv->ifname, sizeof(ireq.i_name));
	ireq.i_type = op;
	ireq.i_val = val;
	ireq.i_data = (void *) arg;
	ireq.i_len = arg_len;

	if (ioctl(drv->global->sock, SIOCS80211, &ireq) < 0) {
		wpa_printf(MSG_ERROR, "ioctl[SIOCS80211, op=%u, val=%u, "
			   "arg_len=%u]: %s", op, val, arg_len,
			   strerror(errno));
		return -1;
	}
	return 0;
}
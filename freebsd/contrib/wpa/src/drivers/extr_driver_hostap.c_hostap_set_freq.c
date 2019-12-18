#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ e; int /*<<< orphan*/  m; } ;
struct TYPE_4__ {TYPE_1__ freq; } ;
struct iwreq {TYPE_2__ u; int /*<<< orphan*/  ifr_name; } ;
struct hostapd_freq_params {int /*<<< orphan*/  channel; } ;
struct hostap_driver_data {int /*<<< orphan*/  ioctl_sock; int /*<<< orphan*/  iface; } ;
typedef  int /*<<< orphan*/  iwr ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  SIOCSIWFREQ ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwreq*) ; 
 int /*<<< orphan*/  os_memset (struct iwreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hostap_set_freq(void *priv, struct hostapd_freq_params *freq)
{
	struct hostap_driver_data *drv = priv;
	struct iwreq iwr;

	os_memset(&iwr, 0, sizeof(iwr));
	os_strlcpy(iwr.ifr_name, drv->iface, IFNAMSIZ);
	iwr.u.freq.m = freq->channel;
	iwr.u.freq.e = 0;

	if (ioctl(drv->ioctl_sock, SIOCSIWFREQ, &iwr) < 0) {
		wpa_printf(MSG_ERROR, "ioctl[SIOCSIWFREQ]: %s",
			   strerror(errno));
		return -1;
	}

	return 0;
}
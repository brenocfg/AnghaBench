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
struct wpa_driver_privsep_data {int /*<<< orphan*/  priv_addr; int /*<<< orphan*/  priv_socket; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  errno ; 
 int sendto (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpa_priv_reg_cmd(struct wpa_driver_privsep_data *drv, int cmd)
{
	int res;

	res = sendto(drv->priv_socket, &cmd, sizeof(cmd), 0,
		     (struct sockaddr *) &drv->priv_addr,
		     sizeof(drv->priv_addr));
	if (res < 0)
		wpa_printf(MSG_ERROR, "sendto: %s", strerror(errno));
	return res < 0 ? -1 : 0;
}
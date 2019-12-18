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
struct wps_er {scalar_t__ multicast_sd; scalar_t__ ssdp_sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_TYPE_READ ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  eloop_unregister_sock (scalar_t__,int /*<<< orphan*/ ) ; 

void wps_er_ssdp_deinit(struct wps_er *er)
{
	if (er->multicast_sd >= 0) {
		eloop_unregister_sock(er->multicast_sd, EVENT_TYPE_READ);
		close(er->multicast_sd);
	}
	if (er->ssdp_sd >= 0) {
		eloop_unregister_sock(er->ssdp_sd, EVENT_TYPE_READ);
		close(er->ssdp_sd);
	}
}
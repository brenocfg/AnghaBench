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
typedef  int /*<<< orphan*/  u8 ;
struct wps_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wps_process_conn_type_flags(struct wps_data *wps, const u8 *conn)
{
	if (conn == NULL) {
		wpa_printf(MSG_DEBUG, "WPS: No Connection Type flags "
			   "received");
		return -1;
	}

	wpa_printf(MSG_DEBUG, "WPS: Enrollee Connection Type flags 0x%x",
		   *conn);

	return 0;
}
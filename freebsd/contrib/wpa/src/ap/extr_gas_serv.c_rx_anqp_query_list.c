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
struct hostapd_data {int dummy; } ;
struct anqp_query_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPA_GET_LE16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  rx_anqp_query_list_id (struct hostapd_data*,int /*<<< orphan*/ ,struct anqp_query_info*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static void rx_anqp_query_list(struct hostapd_data *hapd,
			       const u8 *pos, const u8 *end,
			       struct anqp_query_info *qi)
{
	wpa_printf(MSG_DEBUG, "ANQP: %u Info IDs requested in Query list",
		   (unsigned int) (end - pos) / 2);

	while (end - pos >= 2) {
		rx_anqp_query_list_id(hapd, WPA_GET_LE16(pos), qi);
		pos += 2;
	}
}
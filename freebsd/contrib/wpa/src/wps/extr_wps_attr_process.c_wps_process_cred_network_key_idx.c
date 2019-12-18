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
struct wps_credential {int /*<<< orphan*/  key_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int wps_process_cred_network_key_idx(struct wps_credential *cred,
					    const u8 *key_idx)
{
	if (key_idx == NULL)
		return 0; /* optional attribute */

	wpa_printf(MSG_DEBUG, "WPS: Network Key Index: %d", *key_idx);
	cred->key_idx = *key_idx;

	return 0;
}
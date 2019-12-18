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
typedef  int /*<<< orphan*/  u16 ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_PA_GAS_INITIAL_RESP ; 
 struct wpabuf* gas_build_resp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

struct wpabuf *
gas_build_initial_resp(u8 dialog_token, u16 status_code, u16 comeback_delay,
		       size_t size)
{
	return gas_build_resp(WLAN_PA_GAS_INITIAL_RESP, dialog_token,
			      status_code, 0, 0, comeback_delay, size);
}
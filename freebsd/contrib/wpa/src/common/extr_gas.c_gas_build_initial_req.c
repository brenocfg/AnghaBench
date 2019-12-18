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
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_PA_GAS_INITIAL_REQ ; 
 struct wpabuf* gas_build_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

struct wpabuf * gas_build_initial_req(u8 dialog_token, size_t size)
{
	return gas_build_req(WLAN_PA_GAS_INITIAL_REQ, dialog_token,
			     size);
}
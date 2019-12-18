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
typedef  int u8 ;

/* Variables and functions */
 int const WLAN_EID_EXTENSION ; 
 int const WLAN_EID_EXT_PASSWORD_IDENTIFIER ; 

__attribute__((used)) static int sae_is_password_id_elem(const u8 *pos, const u8 *end)
{
	return end - pos >= 3 &&
		pos[0] == WLAN_EID_EXTENSION &&
		pos[1] >= 1 &&
		end - pos - 2 >= pos[1] &&
		pos[2] == WLAN_EID_EXT_PASSWORD_IDENTIFIER;
}
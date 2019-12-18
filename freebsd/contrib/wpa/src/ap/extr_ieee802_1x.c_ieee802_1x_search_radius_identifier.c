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
struct sta_id_search {struct eapol_state_machine* sm; int /*<<< orphan*/  identifier; } ;
struct hostapd_data {int dummy; } ;
struct eapol_state_machine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ap_for_each_sta (struct hostapd_data*,int /*<<< orphan*/ ,struct sta_id_search*) ; 
 int /*<<< orphan*/  ieee802_1x_select_radius_identifier ; 

__attribute__((used)) static struct eapol_state_machine *
ieee802_1x_search_radius_identifier(struct hostapd_data *hapd, u8 identifier)
{
	struct sta_id_search id_search;
	id_search.identifier = identifier;
	id_search.sm = NULL;
	ap_for_each_sta(hapd, ieee802_1x_select_radius_identifier, &id_search);
	return id_search.sm;
}
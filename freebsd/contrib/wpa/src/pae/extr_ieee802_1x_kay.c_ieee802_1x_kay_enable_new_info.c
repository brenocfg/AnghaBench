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
struct ieee802_1x_mka_participant {scalar_t__ retry_count; scalar_t__ mode; } ;
struct ieee802_1x_kay {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX_RETRY_CNT ; 
 scalar_t__ PSK ; 
 struct ieee802_1x_mka_participant* ieee802_1x_kay_get_principal_participant (struct ieee802_1x_kay*) ; 
 int /*<<< orphan*/  ieee802_1x_participant_send_mkpdu (struct ieee802_1x_mka_participant*) ; 

int ieee802_1x_kay_enable_new_info(struct ieee802_1x_kay *kay)
{
	struct ieee802_1x_mka_participant *principal;

	principal = ieee802_1x_kay_get_principal_participant(kay);
	if (!principal)
		return -1;

	if (principal->retry_count < MAX_RETRY_CNT || principal->mode == PSK) {
		ieee802_1x_participant_send_mkpdu(principal);
		principal->retry_count++;
	}

	return 0;
}
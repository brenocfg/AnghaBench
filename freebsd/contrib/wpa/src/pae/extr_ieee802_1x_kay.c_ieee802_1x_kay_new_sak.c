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
struct ieee802_1x_mka_participant {int /*<<< orphan*/  new_sak; } ;
struct ieee802_1x_kay {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TRUE ; 
 struct ieee802_1x_mka_participant* ieee802_1x_kay_get_principal_participant (struct ieee802_1x_kay*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int
ieee802_1x_kay_new_sak(struct ieee802_1x_kay *kay)
{
	struct ieee802_1x_mka_participant *participant;

	if (!kay)
		return -1;

	participant = ieee802_1x_kay_get_principal_participant(kay);
	if (!participant)
		return -1;

	participant->new_sak = TRUE;
	wpa_printf(MSG_DEBUG, "KaY: new SAK signal");

	return 0;
}
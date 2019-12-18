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
struct mka_key_name {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct ieee802_1x_mka_participant {int /*<<< orphan*/  active; } ;
struct ieee802_1x_kay {int dummy; } ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 struct ieee802_1x_mka_participant* ieee802_1x_kay_get_participant (struct ieee802_1x_kay*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ieee802_1x_kay_mka_participate(struct ieee802_1x_kay *kay,
				    struct mka_key_name *ckn,
				    Boolean status)
{
	struct ieee802_1x_mka_participant *participant;

	if (!kay || !ckn)
		return;

	participant = ieee802_1x_kay_get_participant(kay, ckn->name, ckn->len);
	if (!participant)
		return;

	participant->active = status;
}
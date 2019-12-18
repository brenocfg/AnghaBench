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
struct ieee802_1x_mka_ki {int dummy; } ;
struct ieee802_1x_cp_sm {int /*<<< orphan*/  distributed_ki; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,struct ieee802_1x_mka_ki const*,int) ; 

void ieee802_1x_cp_set_distributedki(void *cp_ctx,
				     const struct ieee802_1x_mka_ki *dki)
{
	struct ieee802_1x_cp_sm *sm = cp_ctx;
	os_memcpy(&sm->distributed_ki, dki, sizeof(struct ieee802_1x_mka_ki));
}
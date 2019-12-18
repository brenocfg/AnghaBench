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
struct ieee802_1x_mka_participant {int dummy; } ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/ * ieee802_1x_kay_get_potential_peer (struct ieee802_1x_mka_participant*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static Boolean
ieee802_1x_kay_is_in_potential_peer(
	struct ieee802_1x_mka_participant *participant, const u8 *mi)
{
	return ieee802_1x_kay_get_potential_peer(participant, mi) != NULL;
}
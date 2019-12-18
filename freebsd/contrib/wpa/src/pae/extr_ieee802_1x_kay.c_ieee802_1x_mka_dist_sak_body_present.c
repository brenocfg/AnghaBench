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
struct ieee802_1x_mka_participant {scalar_t__ new_key; scalar_t__ to_dist_sak; scalar_t__ is_key_server; } ;
typedef  int Boolean ;

/* Variables and functions */

__attribute__((used)) static Boolean
ieee802_1x_mka_dist_sak_body_present(
	struct ieee802_1x_mka_participant *participant)
{
	return participant->is_key_server && participant->to_dist_sak &&
		participant->new_key;
}
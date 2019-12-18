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
struct ikev2_keys {scalar_t__ SK_pr; scalar_t__ SK_pi; scalar_t__ SK_er; scalar_t__ SK_ei; scalar_t__ SK_ar; scalar_t__ SK_ai; scalar_t__ SK_d; } ;

/* Variables and functions */

int ikev2_keys_set(struct ikev2_keys *keys)
{
	return keys->SK_d && keys->SK_ai && keys->SK_ar && keys->SK_ei &&
		keys->SK_er && keys->SK_pi && keys->SK_pr;
}
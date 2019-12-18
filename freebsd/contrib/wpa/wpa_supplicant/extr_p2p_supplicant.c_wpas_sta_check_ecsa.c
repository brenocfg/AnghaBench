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
struct sta_info {int ecsa_supported; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int wpas_sta_check_ecsa(struct hostapd_data *hapd,
			       struct sta_info *sta, void *ctx)
{
	int *ecsa_support = ctx;

	*ecsa_support &= sta->ecsa_supported;

	return 0;
}
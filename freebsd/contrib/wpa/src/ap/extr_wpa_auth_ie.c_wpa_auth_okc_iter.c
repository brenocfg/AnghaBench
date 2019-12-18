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
struct wpa_authenticator {int /*<<< orphan*/  pmksa; } ;
struct wpa_auth_okc_iter_data {scalar_t__ pmksa; int /*<<< orphan*/  pmkid; int /*<<< orphan*/  spa; int /*<<< orphan*/  aa; } ;

/* Variables and functions */
 scalar_t__ pmksa_cache_get_okc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpa_auth_okc_iter(struct wpa_authenticator *a, void *ctx)
{
	struct wpa_auth_okc_iter_data *data = ctx;
	data->pmksa = pmksa_cache_get_okc(a->pmksa, data->aa, data->spa,
					  data->pmkid);
	if (data->pmksa)
		return 1;
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wpa_config_blob {int dummy; } ;
struct eapol_test_data {TYPE_1__* wpa_s; } ;
struct TYPE_2__ {int /*<<< orphan*/  conf; } ;

/* Variables and functions */
 struct wpa_config_blob const* wpa_config_get_blob (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static const struct wpa_config_blob *
eapol_test_get_config_blob(void *ctx, const char *name)
{
	struct eapol_test_data *e = ctx;
	return wpa_config_get_blob(e->wpa_s->conf, name);
}
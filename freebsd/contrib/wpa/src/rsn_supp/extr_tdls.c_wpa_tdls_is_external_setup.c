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
struct wpa_sm {int tdls_external_setup; } ;

/* Variables and functions */

int wpa_tdls_is_external_setup(struct wpa_sm *sm)
{
	return sm->tdls_external_setup;
}
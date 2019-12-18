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
struct hostapd_hw_modes {struct hostapd_hw_modes* rates; struct hostapd_hw_modes* channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct hostapd_hw_modes*) ; 

void hostapd_free_hw_features(struct hostapd_hw_modes *hw_features,
			      size_t num_hw_features)
{
	size_t i;

	if (hw_features == NULL)
		return;

	for (i = 0; i < num_hw_features; i++) {
		os_free(hw_features[i].channels);
		os_free(hw_features[i].rates);
	}

	os_free(hw_features);
}
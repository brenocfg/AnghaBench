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
struct wpa_scan_res {int flags; scalar_t__ level; scalar_t__ snr; scalar_t__ noise; int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_NOISE_FLOOR_2GHZ ; 
 scalar_t__ DEFAULT_NOISE_FLOOR_5GHZ ; 
 scalar_t__ IS_5GHZ (int /*<<< orphan*/ ) ; 
 int WPA_SCAN_LEVEL_DBM ; 
 int WPA_SCAN_NOISE_INVALID ; 

void scan_snr(struct wpa_scan_res *res)
{
	if (res->flags & WPA_SCAN_NOISE_INVALID) {
		res->noise = IS_5GHZ(res->freq) ?
			DEFAULT_NOISE_FLOOR_5GHZ :
			DEFAULT_NOISE_FLOOR_2GHZ;
	}

	if (res->flags & WPA_SCAN_LEVEL_DBM) {
		res->snr = res->level - res->noise;
	} else {
		/* Level is not in dBm, so we can't calculate
		 * SNR. Just use raw level (units unknown). */
		res->snr = res->level;
	}
}
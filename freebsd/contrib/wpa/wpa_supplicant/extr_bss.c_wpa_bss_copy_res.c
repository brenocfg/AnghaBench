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
struct wpa_scan_res {int /*<<< orphan*/  age; int /*<<< orphan*/  snr; int /*<<< orphan*/  est_throughput; int /*<<< orphan*/  tsf; int /*<<< orphan*/  level; int /*<<< orphan*/  noise; int /*<<< orphan*/  qual; int /*<<< orphan*/  caps; int /*<<< orphan*/  beacon_int; int /*<<< orphan*/  freq; int /*<<< orphan*/  bssid; int /*<<< orphan*/  flags; } ;
struct wpa_bss {int /*<<< orphan*/  last_update; int /*<<< orphan*/  snr; int /*<<< orphan*/  est_throughput; int /*<<< orphan*/  tsf; int /*<<< orphan*/  level; int /*<<< orphan*/  noise; int /*<<< orphan*/  qual; int /*<<< orphan*/  caps; int /*<<< orphan*/  beacon_int; int /*<<< orphan*/  freq; int /*<<< orphan*/  bssid; int /*<<< orphan*/  flags; } ;
struct os_reltime {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  calculate_update_time (struct os_reltime*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpa_bss_copy_res(struct wpa_bss *dst, struct wpa_scan_res *src,
			     struct os_reltime *fetch_time)
{
	dst->flags = src->flags;
	os_memcpy(dst->bssid, src->bssid, ETH_ALEN);
	dst->freq = src->freq;
	dst->beacon_int = src->beacon_int;
	dst->caps = src->caps;
	dst->qual = src->qual;
	dst->noise = src->noise;
	dst->level = src->level;
	dst->tsf = src->tsf;
	dst->est_throughput = src->est_throughput;
	dst->snr = src->snr;

	calculate_update_time(fetch_time, src->age, &dst->last_update);
}
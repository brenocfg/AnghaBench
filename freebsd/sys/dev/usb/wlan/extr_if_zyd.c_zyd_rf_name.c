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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static const char *
zyd_rf_name(uint8_t type)
{
	static const char * const zyd_rfs[] = {
		"unknown", "unknown", "UW2451",   "UCHIP",     "AL2230",
		"AL7230B", "THETA",   "AL2210",   "MAXIM_NEW", "GCT",
		"AL2230S",  "RALINK",  "INTERSIL", "RFMD",      "MAXIM_NEW2",
		"PHILIPS"
	};

	return zyd_rfs[(type > 15) ? 0 : type];
}
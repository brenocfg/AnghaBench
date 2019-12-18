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

/* Variables and functions */
#define  RT2661_RF_2527 131 
#define  RT2661_RF_2529 130 
#define  RT2661_RF_5225 129 
#define  RT2661_RF_5325 128 

__attribute__((used)) static const char *
rt2661_get_rf(int rev)
{
	switch (rev) {
	case RT2661_RF_5225:	return "RT5225";
	case RT2661_RF_5325:	return "RT5325 (MIMO XR)";
	case RT2661_RF_2527:	return "RT2527";
	case RT2661_RF_2529:	return "RT2529 (MIMO XR)";
	default:		return "unknown";
	}
}
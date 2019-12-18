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
#define  RT2573_RF_2527 131 
#define  RT2573_RF_2528 130 
#define  RT2573_RF_5225 129 
#define  RT2573_RF_5226 128 

__attribute__((used)) static const char *
rum_get_rf(int rev)
{
	switch (rev) {
	case RT2573_RF_2527:	return "RT2527 (MIMO XR)";
	case RT2573_RF_2528:	return "RT2528";
	case RT2573_RF_5225:	return "RT5225 (MIMO XR)";
	case RT2573_RF_5226:	return "RT5226";
	default:		return "unknown";
	}
}
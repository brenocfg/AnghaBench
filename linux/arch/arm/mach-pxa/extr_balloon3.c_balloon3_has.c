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
typedef  enum balloon3_features { ____Placeholder_balloon3_features } balloon3_features ;

/* Variables and functions */
 int balloon3_features_present ; 

int balloon3_has(enum balloon3_features feature)
{
	return (balloon3_features_present & (1 << feature)) ? 1 : 0;
}
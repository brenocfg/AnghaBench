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
typedef  int int32_t ;

/* Variables and functions */
 int MINSPERHR ; 
 int SECSPERMIN ; 

int32_t
ntpcal_etime_to_seconds(
	int32_t hours,
	int32_t minutes,
	int32_t seconds
	)
{
	int32_t res;

	res = (hours * MINSPERHR + minutes) * SECSPERMIN + seconds;

	return res;
}
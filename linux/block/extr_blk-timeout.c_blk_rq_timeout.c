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
 scalar_t__ BLK_MAX_TIMEOUT ; 
 scalar_t__ jiffies ; 
 unsigned long round_jiffies_up (scalar_t__) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

unsigned long blk_rq_timeout(unsigned long timeout)
{
	unsigned long maxt;

	maxt = round_jiffies_up(jiffies + BLK_MAX_TIMEOUT);
	if (time_after(timeout, maxt))
		timeout = maxt;

	return timeout;
}
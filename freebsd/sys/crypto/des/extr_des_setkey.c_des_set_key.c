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
typedef  int /*<<< orphan*/  des_key_schedule ;

/* Variables and functions */
 scalar_t__ des_check_key ; 
 int des_set_key_checked (unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  des_set_key_unchecked (unsigned char const*,int /*<<< orphan*/ ) ; 

int des_set_key(const unsigned char *key, des_key_schedule schedule)
{
	if (des_check_key)
	{
		return des_set_key_checked(key, schedule);
	}
	else
	{
		des_set_key_unchecked(key, schedule);
		return 0;
	}
}
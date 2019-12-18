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
 int CERASE ; 
 int* key_backspace ; 
 scalar_t__ over_strike ; 
 int strlen (int*) ; 

__attribute__((used)) static int
default_erase(void)
{
    int result;

    if (over_strike
	&& key_backspace != 0
	&& strlen(key_backspace) == 1)
	result = key_backspace[0];
    else
	result = CERASE;

    return result;
}
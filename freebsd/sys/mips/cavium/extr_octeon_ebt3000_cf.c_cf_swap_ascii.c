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
 int MODEL_STR_SIZE ; 

__attribute__((used)) static void cf_swap_ascii (unsigned char str1[], char str2[])
{
	int i;

	for(i = 0; i < MODEL_STR_SIZE; i++)
		str2[i] = str1[i ^ 1];
}
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
typedef  int uint32_t ;

/* Variables and functions */
 int A83T_TEMP_BASE ; 
 int A83T_TEMP_DIV ; 
 int A83T_TEMP_MUL ; 

__attribute__((used)) static int
a83t_to_temp(uint32_t val, int sensor)
{
	return ((A83T_TEMP_BASE - (val * A83T_TEMP_MUL)) / A83T_TEMP_DIV);
}
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
 scalar_t__* code ; 
 size_t pc ; 

__attribute__((used)) static int NextConstant4(void)
{
	return ((unsigned int)code[pc] | ((unsigned int)code[pc+1]<<8) | ((unsigned int)code[pc+2]<<16) | ((unsigned int)code[pc+3]<<24));
}
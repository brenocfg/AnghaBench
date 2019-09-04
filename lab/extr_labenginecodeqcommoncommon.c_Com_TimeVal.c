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
 int Sys_Milliseconds () ; 
 int com_frameTime ; 

int Com_TimeVal(int minMsec)
{
	int timeVal;

	timeVal = Sys_Milliseconds() - com_frameTime;

	if(timeVal >= minMsec)
		timeVal = 0;
	else
		timeVal = minMsec - timeVal;

	return timeVal;
}
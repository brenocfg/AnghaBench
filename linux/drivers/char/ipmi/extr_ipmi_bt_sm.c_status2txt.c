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
 unsigned char BT_B2H_ATN ; 
 unsigned char BT_B_BUSY ; 
 unsigned char BT_H2B_ATN ; 
 unsigned char BT_H_BUSY ; 
 unsigned char BT_OEM0 ; 
 unsigned char BT_SMS_ATN ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static char *status2txt(unsigned char status)
{
	/*
	 * This cannot be called by two threads at the same time and
	 * the buffer is always consumed immediately, so the static is
	 * safe to use.
	 */
	static char buf[40];

	strcpy(buf, "[ ");
	if (status & BT_B_BUSY)
		strcat(buf, "B_BUSY ");
	if (status & BT_H_BUSY)
		strcat(buf, "H_BUSY ");
	if (status & BT_OEM0)
		strcat(buf, "OEM0 ");
	if (status & BT_SMS_ATN)
		strcat(buf, "SMS ");
	if (status & BT_B2H_ATN)
		strcat(buf, "B2H ");
	if (status & BT_H2B_ATN)
		strcat(buf, "H2B ");
	strcat(buf, "]");
	return buf;
}
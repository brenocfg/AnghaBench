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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static const char *
format_timestamp(uint32_t timestamp)
{
	static char buffer[32];

	if ((timestamp & 0xff000000) == 0xff000000)
		snprintf(buffer, sizeof(buffer), "boot + %us", timestamp &
		    0x00ffffff);
	else
		snprintf(buffer, sizeof(buffer), "%us", timestamp);
	return (buffer);
}